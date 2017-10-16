using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// When this script is added to a gameobject, it will check if the required
// components exist and add them if not
[RequireComponent(typeof(MeshFilter))]
[RequireComponent(typeof(MeshRenderer))]

public class GenerateMesh : MonoBehaviour {


	Mesh mesh;
	Vector3 [] vertices;
	Color[] colors;
	public Gradient coloring;

	int xSize = 50;
	int ySize = 50;
	float scale = 2F;

	[Range(1F,500F)]
	public float freq = 100.0F;
	[Range(1,10)]
	public int octaves = 4;
	[Range(1F,500F)]
	public float amp = 100F;


	// Use this for initialization
	void Start () {


		mesh = new Mesh();
		mesh.name = "Grid";


		vertices = new Vector3[ (xSize + 1) * (ySize + 1) ];
		colors = new Color[vertices.Length];

		for (int i = 0, y = 0; y < ySize; y++) {
			for (int x = 0; x < xSize; x++, i++) {

				float colorVal = 1F;
				colors[i] = coloring.Evaluate( colorVal );
				vertices[i] = new Vector3(x*scale,0F, y*scale);
			}
		}
		mesh.vertices = vertices;
		mesh.colors = colors;


		int[] triangles = new int[xSize * ySize * 6];
		for (int t = 0, v = 0, y = 0; y < ySize; y++, v++) {
			for (int x = 0; x < xSize; x++, v++, t += 6) {
				triangles[t] = v;
				triangles[t + 1] = v + xSize + 1;
				triangles[t + 2] = v + 1;
				triangles[t + 3] = v + 1;
				triangles[t + 4] = v + xSize + 1;
				triangles[t + 5] = v + xSize + 2;
			}
		}
		mesh.triangles = triangles;

		mesh.RecalculateNormals();

		GetComponent<MeshFilter>().mesh = mesh;
	}
	
	// Update is called once per frame
	void Update () {

		float time = Time.time * 5F;
			
		for (int i = 0, y = 0; y <= ySize; y++) {
			for (int x = 0; x <= xSize; x++, i++) {

				float noiseVal = 0F;
				float gain = 1F;
				for(int j = 0; j < octaves; j++){

					noiseVal +=  Mathf.PerlinNoise( (x+time)*gain/freq, (y+time)*gain/freq) * amp/gain;
					gain *= 2.0F;

				}

				float colorVal = (noiseVal- amp*.5F) / (amp*.5F);
				colors[i] = coloring.Evaluate( colorVal );
				vertices[i] = new Vector3(x*scale - .5F*(xSize*scale), noiseVal - amp*.5F, y*scale- .5F*(ySize*scale));
			}
		}
		mesh.vertices = vertices;
		mesh.colors = colors;
		mesh.RecalculateNormals();
	}
}
