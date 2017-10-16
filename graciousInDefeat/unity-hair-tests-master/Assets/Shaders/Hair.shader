Shader "Custom/Hair" {
	Properties{
		_TransparencyMask("Hair Transparency Mask", 2D) = "white" {}
		_Colour("Colour", Color) = (0,0,0,1)
		_Length("Length",Range(0.001,1)) = 0.04
		_Width("Width",Range(0.001,1)) = 0.02
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


			sampler2D _TransparencyMask;
			float _Length;
			float _Width;
			float4 _Colour;

			appdata_hair_gs vert(appdata_hair_vs hairVertex) {
				return BuildGeometryShaderData(hairVertex.position, hairVertex.normal, hairVertex.tangent, hairVertex.uv);
			}

			[maxvertexcount(4)]
			void geom(point appdata_hair_gs _input[1], inout TriangleStream<v2f> triangleStream) {
				appdata_hair_gs hairVertex = _input[0];
#if defined(USE_NORMAL_FOR_DIRECTION)
				float3 direction = hairVertex.normal;

#elif defined(USE_TANGENT_FOR_DIRECTION)
				float3 direction = hairVertex.tangent;
#else
				//float3 direction = cross(hairVertex.normal, hairVertex.tangent);
				float3 direction = (hairVertex.normal.y > 0 ? cross(hairVertex.normal, hairVertex.tangent) : float3(0,-1,0));
#endif
				float3 tangent = GetFaceTangent(hairVertex.normal);
				BuildSprite(hairVertex.position, _Width, _Length, direction, tangent, hairVertex.uv, triangleStream);
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