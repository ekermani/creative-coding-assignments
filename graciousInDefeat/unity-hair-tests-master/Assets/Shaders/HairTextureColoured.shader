Shader "Custom/HairTextureColoured" {
	Properties{
		_TransparencyMask("Hair Transparency Mask", 2D) = "white" {}
		_Colour("Colour", 2D) = "white" {}
		_Length("Length",Range(0.001,1)) = 0.04
		_Width("Width",Range(0.001,1)) = 0.02
		[Toggle(ENABLE_EDGE_SPRITES)]
		_EnableEdgeSprites("Enable Edge Sprites", float) = 1
		[Toggle(ENABLE_CENTER_SPRITE)]
		_EnableCenterSprite("Enable Center Sprites", float) = 1
		_Direction("Direction", Vector) = (0,0,0,1)
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

			#define APPLY_TRANSPARENCY_MASK_TO_COLOUR
			#pragma shader_feature ENABLE_EDGE_SPRITES
			#pragma shader_feature ENABLE_CENTER_SPRITE


			sampler2D _TransparencyMask;
			sampler2D _Colour;
			float _Length;
			float _Width;
			float4 _Direction;

			appdata_hair_gs vert(appdata_hair_vs hairVertex) {
				return BuildGeometryShaderData(hairVertex.position, hairVertex.normal, hairVertex.tangent, hairVertex.uv);
			}


			void AddEdgeVertexToTriangleStream(appdata_hair_gs hairVertex1, appdata_hair_gs hairVertex2, float3 tangent, inout TriangleStream<v2f> triangleStream) {
				float3 position = hairVertex1.position + ((hairVertex2.position - hairVertex1.position) * 0.5f);
				float3 direction = normalize(_Direction.xyz);
				float2 hairuv = (hairVertex1.uv + hairVertex2.uv) * 0.5f;
				BuildSprite(position, _Width, _Length, direction, tangent, hairuv, triangleStream);
			}

			void AddEdgeVerticesToTriangleStream(appdata_hair_gs hairVertices[3], inout TriangleStream<v2f> triangleStream) {
				float3 normal = GetFaceNormal(hairVertices);
				float3 tangent = GetFaceTangent(normal);

				AddEdgeVertexToTriangleStream(hairVertices[0], hairVertices[1], tangent, triangleStream);
				AddEdgeVertexToTriangleStream(hairVertices[0], hairVertices[2], tangent, triangleStream);
				AddEdgeVertexToTriangleStream(hairVertices[2], hairVertices[1], tangent, triangleStream);
			}

			void AddTriangleCenterVertexToTriangleStream(appdata_hair_gs hairVertices[3], inout TriangleStream<v2f> triangleStream) {
				float3 position = GetTriangleCenter(hairVertices);
				float3 normal = GetFaceNormal(hairVertices);
				float3 tangent = GetFaceTangent(normal);
				float2 hairuv = (hairVertices[0].uv + hairVertices[1].uv + hairVertices[2].uv) / 3;

				//float3 direction = _Direction.xyz;
				float3 direction = normalize(_Direction.xyz);

				BuildSprite(position, _Width, _Length, direction, tangent, hairuv, triangleStream);
			}


			[maxvertexcount(16)]
			void geom(triangle appdata_hair_gs _input[3], inout TriangleStream<v2f> triangleStream) {
#if defined(ENABLE_EDGE_SPRITES)
				AddEdgeVerticesToTriangleStream(_input, triangleStream);
#endif

#if defined(ENABLE_CENTER_SPRITE)
				AddTriangleCenterVertexToTriangleStream(_input, triangleStream);
#endif
			}

			fixed4 frag(v2f i) : SV_Target{
				// sample the texture
				float4 transparencyMask = tex2D(_TransparencyMask, i.uv);
				float4 colour = tex2D(_Colour, i.hairuv);

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