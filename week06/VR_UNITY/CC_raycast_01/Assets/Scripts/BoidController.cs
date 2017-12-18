/*
https://github.com/keijiro/unity-boids
*/

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BoidController : MonoBehaviour {

	public GameObject prefab;
	public int number = 200;

	public float boidSpeed = 0.1f;
	public float boidYawing = 90.0f;

	void Awake(){
		Boid.globalTarget = gameObject;
		Boid.globalSpeed = boidSpeed;
		Boid.globalYawing = boidYawing;
	}

	// Use this for initialization
	void Start () {
		for (int i = 0; i < number; i++) {
        	Instantiate(prefab);
        	// add delay?
    	}
	}
	
	// Update is called once per frame
	void Update () {
		Boid.globalSpeed = boidSpeed;
		Boid.globalYawing = boidYawing;
	}
}
