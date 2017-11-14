using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Sphere : MonoBehaviour {

	Vector3 origin;
	Vector3 vel;

	// Use this for initialization
	void Start () {
		origin = transform.position;
		vel = Vector3.zero;
	}
	
	// Update is called once per frame
	void Update () {

		if (GetComponent<Rigidbody> ().isKinematic) {
			Vector3 pos = transform.position;

			Vector3 home = origin - transform.position ;
			pos += 2f* home * Time.deltaTime;

			pos += vel * Time.deltaTime;

			vel *= .99f;

			transform.position = pos;
		}
	}

	public void addVelocity(Vector3 _vel){
		vel += _vel;
	}
}
