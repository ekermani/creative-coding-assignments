/*
https://github.com/keijiro/unity-boids
*/

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Boid : MonoBehaviour {

	public static GameObject globalTarget;

	public static float globalSpeed = 0.1f;
	public static float globalYawing = 90.0f;

	private float speedScale = 1.0f;
	private float yawingScale = 1.0f;

	// Use this for initialization
	void Start () {
		transform.rotation = Random.rotation;
		speedScale = Random.Range(0.8f, 1.2f);
		yawingScale = Random.Range(0.8f, 1.2f);
	}

	// Update is called once per frame
	void Update () {
		transform.position += transform.forward * (globalSpeed * speedScale * Time.deltaTime);
		Quaternion rotation = Quaternion.FromToRotation(transform.forward, globalTarget.transform.position - transform.position);
		transform.rotation = Quaternion.RotateTowards(Quaternion.identity, rotation, globalYawing * yawingScale * Time.deltaTime) * transform.rotation;

	}
}
