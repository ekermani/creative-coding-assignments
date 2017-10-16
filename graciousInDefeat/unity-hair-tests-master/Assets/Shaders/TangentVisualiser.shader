// Upgrade NOTE: replaced '_Object2World' with 'unity_ObjectToWorld'
// Upgrade NOTE: replaced 'mul(UNITY_MATRIX_MVP,*)' with 'UnityObjectToClipPos(*)'
// Source: https://forum.unity3d.com/threads/ending-the-confusion-about-mirrored-normal-mapping.409698/
Shader "TangentVisualiser" {
	Properties{
		_MainTex("Base (RGB)", 2D) = "white" {}
		[NoScaleOffset] _BumpMap("Normal Map", 2D) = "bump" {}
		[KeywordEnum(Lit, Mesh Normals, Mesh Tangents, Mesh Bitangents, Tangent Normals, World Normals)] _Display("Debug Display", Float) = 0
		[Toggle(_DERIVATIVES_ON)] _Derivatives("Debug Use Derivatives", Float) = 0
		[Enum(Zero to One, 0, Normalized, 1, Inverted, 2, Absolute, 3)] _Normalization("Vector Display", Float) = 0
	}

		SubShader{
		Tags{ "RenderType" = "Opaque" "LightMode" = "ForwardBase" }
		LOD 100

		Pass{
		CGPROGRAM
#pragma vertex vert
#pragma fragment frag
#pragma shader_feature _ _DISPLAY_MESH_NORMALS _DISPLAY_MESH_TANGENTS _DISPLAY_MESH_BITANGENTS _DISPLAY_TANGENT_NORMALS _DISPLAY_WORLD_NORMALS
#pragma shader_feature _ _DERIVATIVES_ON

#include "UnityCG.cginc"

		struct v2f {
		float4 vertex : SV_POSITION;
		half2 texcoord : TEXCOORD0;
#ifdef _DERIVATIVES_ON
		half3 normal : TEXCOORD1;
		float3 pos : TEXCOORD2;
#else
		half3x3 tspace : TEXCOORD1;
#endif
	};

	sampler2D _MainTex;
	float4 _MainTex_ST;
	sampler2D _BumpMap;

	fixed4 _LightColor0;
	float _Normalization;

	float3x3 cotangent_frame(float3 normal, float3 position, float2 uv)
	{
		// get edge vectors of the pixel triangle
		float3 dp1 = ddx(position);
		float3 dp2 = ddy(position) * _ProjectionParams.x;
		float2 duv1 = ddx(uv);
		float2 duv2 = ddy(uv) * _ProjectionParams.x;

		// solve the linear system
		float3 dp2perp = cross(dp2, normal);
		float3 dp1perp = cross(normal, dp1);
		float3 T = dp2perp * duv1.x + dp1perp * duv2.x;
		float3 B = dp2perp * duv1.y + dp1perp * duv2.y;

		// construct a scale-invariant frame
		// float invmax = rsqrt( max( dot(T,T), dot(B,B) ) );
		// return transpose(float3x3( T * invmax, B * invmax, normal ));
		return transpose(float3x3(normalize(T), normalize(B), normal));
	}

	fixed4 rescaleForVis(half3 vec)
	{
		vec = normalize(vec);
		if (_Normalization == 3.0)
			return fixed4(abs(vec), 1.0);
		if (_Normalization == 2.0)
			return fixed4(-vec, 1.0);
		if (_Normalization == 1.0)
			return fixed4(vec, 1.0);
		// if (_Normalization == 0.0)
		return fixed4(vec * 0.5 + 0.5, 1.0);
	}

	v2f vert(appdata_full v)
	{
		v2f o;
		o.vertex = UnityObjectToClipPos(v.vertex);
		o.texcoord = TRANSFORM_TEX(v.texcoord, _MainTex);

#ifdef _DERIVATIVES_ON
		o.normal = UnityObjectToWorldNormal(v.normal);
		o.pos = mul(unity_ObjectToWorld, v.vertex);
#else
		half3 wNormal = UnityObjectToWorldNormal(v.normal);
		half3 wTangent = UnityObjectToWorldDir(v.tangent.xyz);
		// compute bitangent from cross product of normal and tangent
		half tangentSign = v.tangent.w * unity_WorldTransformParams.w;
		half3 wBitangent = cross(wNormal, wTangent) * tangentSign;
		// output the tangent space matrix
		o.tspace = half3x3(wTangent.x, wBitangent.x, wNormal.x,
			wTangent.y, wBitangent.y, wNormal.y,
			wTangent.z, wBitangent.z, wNormal.z);
#endif
		return o;
	}

	fixed4 frag(v2f i) : SV_Target
	{
		half3x3 tbn;
#ifdef _DERIVATIVES_ON
	tbn = cotangent_frame(i.normal, i.pos, i.texcoord);
#else
	tbn = i.tspace;
#endif

#ifdef _DISPLAY_MESH_NORMALS
	return rescaleForVis(half3(tbn[0].z, tbn[1].z, tbn[2].z));
#endif

#ifdef _DISPLAY_MESH_TANGENTS
	return rescaleForVis(half3(tbn[0].x, tbn[1].x, tbn[2].x));
#endif

#ifdef _DISPLAY_MESH_BITANGENTS
	return rescaleForVis(half3(tbn[0].y, tbn[1].y, tbn[2].y));
#endif

	half3 tnormal = UnpackNormal(tex2D(_BumpMap, i.texcoord));

#ifdef _DISPLAY_TANGENT_NORMALS
	return rescaleForVis(tnormal);
#endif

	half3 worldNormal = normalize(mul(tbn, tnormal));

#ifdef _DISPLAY_WORLD_NORMALS
	return rescaleForVis(worldNormal);
#endif

	fixed4 col = tex2D(_MainTex, i.texcoord);
	half ndotl = dot(worldNormal, _WorldSpaceLightPos0.xyz);
	col.rgb *= saturate(ndotl) * _LightColor0.rgb + ShadeSH9(float4(worldNormal,1.0));

	return col;
	}
		ENDCG
	}
	}

}