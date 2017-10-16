using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HairAnimation : MonoBehaviour {

	public float smooth = 20.0f;
	public float tiltAngle = 30.0f;
	public float yRotation = 5.0f;

	public float rotationDegreesPerSecond = 45f;
	public float rotationDegreesAmount = 90f;
	private float totalRotation = 5;
	public float degreesPerSecond = 30;

	void Start() {
	}

	void Update() {
		
		if(Mathf.Abs(totalRotation) < Mathf.Abs(rotationDegreesAmount))
			Hair (); 
		

//		float tiltAroundZ = Input.GetAxis("Horizontal") * tiltAngle;
//		float tiltAroundX = Input.GetAxis("Vertical") * tiltAngle;
//		Quaternion target = Quaternion.Euler(tiltAroundX, 0, tiltAroundZ);
//		transform.rotation = Quaternion.Slerp(transform.rotation, target, Time.deltaTime * smooth);

//		yRotation += Input.GetAxis("Horizontal");
//		transform.eulerAngles = new Vector3(10, yRotation, 0);
	}

	void Hair() {


//		print(transform.eulerAngles.x);
//		print(transform.eulerAngles.y);
//		print(transform.eulerAngles.z);

//		Quaternion newRotation = new Quaternion(transform.rotation.x,transform.rotation.y,transform.rotation.z,transform.rotation.w);;
//		newRotation *= Quaternion.Euler(0, 90, 0); // this add a 90 degrees Y rotation
//		transform.rotation= Quaternion.Slerp(transform.rotation, newRotation,20 * Time.deltaTime); 

		float currentAngle = transform.rotation.eulerAngles.y;
		transform.rotation = Quaternion.AngleAxis(currentAngle + (Time.deltaTime * degreesPerSecond), Vector3.up);
		totalRotation += Time.deltaTime * degreesPerSecond;
	}
}

