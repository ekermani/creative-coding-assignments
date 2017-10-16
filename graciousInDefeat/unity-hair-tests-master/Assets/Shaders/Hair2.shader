Shader "Custom/Hair2" {
	Properties{
		_TransparencyMask("Hair Transparency Mask", 2D) = "white" {}
		_Colour("Colour", Color) = (0,0,0,1)
		_Length("Length",Range(0.001,1)) = 0.04
		_Width("Width",Range(0.001,1)) = 0.02
		[Toggle(ENABLE_EDGE_SPRITES)]
		_EnableEdgeSprites("Enable Edge Sprites", float) = 1
		[Toggle(ENABLE_CENTER_SPRITE)]
		_EnableCenterSprite("Enable Center Sprites", float) = 1
	}

	SubShader{
		Tags{ "Queue" = "Transparent" "RenderType" = "Transparent" "IgnoreProjector" = "True" }
		LOD 100
		Cull off
		ZWrite Off
		Blend SrcAlpha OneMinusSrcAlpha // Traditional transparency

		Pass{
			CGPROGRAM

			//	Using geometry shader so target 4.0
			//	https://docs.unity3d.com/Manual/SL-ShaderCompileTargets.html
			#pragma target 4.0

			#pragma vertex vert
			#pragma fragment frag
			#pragma geometry geom

			#include "Hair.cginc"

			//#define USE_NORMAL_FOR_DIRECTION
			//#define USE_TANGENT_FOR_DIRECTION
			#define APPLY_TRANSPARENCY_MASK_TO_COLOUR
			#pragma shader_feature ENABLE_EDGE_SPRITES
			#pragma shader_feature ENABLE_CENTER_SPRITE

			sampler2D _TransparencyMask;
			float _Length;
			float _Width;
			float4 _Colour;

			appdata_hair_gs vert(appdata_hair_vs hairVertex) {
				return BuildGeometryShaderData(hairVertex.position, hairVertex.normal, hairVertex.tangent, hairVertex.uv);
			}

			void AddEdgeVertexToTriangleStream(appdata_hair_gs hairVertex1, appdata_hair_gs hairVertex2, inout TriangleStream<v2f> triangleStream) {
				float3 position = hairVertex1.position + ((hairVertex2.position - hairVertex1.position) * 0.5f);
				float3 normal = (hairVertex1.normal + hairVertex2.normal) / 2;
				float3 tangent = GetFaceTangent(normal);
				float2 hairuv = (hairVertex1.uv + hairVertex2.uv) / 2;
#if defined(USE_NORMAL_FOR_DIRECTION)
				float3 direction = hairVertex1.normal;
#elif defined(USE_TANGENT_FOR_DIRECTION)
				float3 direction = tangent;
#else
				//float3 direction = cross(normal, tangent);
				float3 direction = (normal.y > 0 ? cross(normal, tangent) : float3(0, -1, 0));
#endif
				BuildSprite(position, _Width, _Length, direction, tangent, hairuv, triangleStream);
			}

			void AddTriangleCenterVertexToTriangleStream(appdata_hair_gs hairVertices[3], inout TriangleStream<v2f> triangleStream) {
				float3 position = GetTriangleCenter(hairVertices);
				float3 normal = (hairVertices[0].normal + hairVertices[1].normal + hairVertices[2].normal) / 3;
				float3 tangent = GetFaceTangent(normal);
				float2 hairuv = (hairVertices[0].uv + hairVertices[1].uv + hairVertices[2].uv) / 3;

#if defined(USE_NORMAL_FOR_DIRECTION)
				float3 direction = normal;
#elif defined(USE_TANGENT_FOR_DIRECTION)
				float3 direction = tangent;
#else
				//float3 direction = cross(normal, tangent);
				float3 direction = (normal.y > 0 ? cross(normal, tangent) : float3(0, -1, 0));
#endif
				BuildSprite(position, _Width, _Length, direction, tangent, hairuv, triangleStream);
			}


			[maxvertexcount(16)]
			void geom(triangle appdata_hair_gs _input[3], inout TriangleStream<v2f> triangleStream) {
#if defined(ENABLE_EDGE_SPRITES)
				AddEdgeVertexToTriangleStream(_input[0], _input[1], triangleStream);
				AddEdgeVertexToTriangleStream(_input[0], _input[2], triangleStream);
				AddEdgeVertexToTriangleStream(_input[2], _input[1], triangleStream);
#endif

#if defined(ENABLE_CENTER_SPRITE)
				AddTriangleCenterVertexToTriangleStream(_input, triangleStream);
#endif
			}

			fixed4 frag(v2f i) : SV_Target{
				// sample the texture
				float4 transparencyMask = tex2D(_TransparencyMask, i.uv);
				float3 colour = _Colour.xyz;

#if defined(APPLY_TRANSPARENCY_MASK_TO_COLOUR)
				return float4(colour.xyz * transparencyMask.xyz, transparencyMask.x);
#else
				return float4(colour.xyz, transparencyMask.x);
#endif
			}
			ENDCG
		}
	}
}