using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//monobehaviour - base unity game object class
//cube now has access to all the features+behaviours of the class
public class CubeMoves : MonoBehaviour {

    //data types for variables:
        //put f after floating values
        //public = shows up in inspector
    public float rotationSpeed = 50.1f;

    // Called before Start
    //1. typically used to initialize values of the game object here 
    void Awake () {

    }

	// Use this for initialization
    //2. make connections to other game objects
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        //gameObject = always referring to this object (cube) - like saying "this", reffering to itself
        //vector3 = has x, y, z inside of it + lets you do vector math, useful because we can get directions (vector3.up, vector3.forward, etc)
        Vector3 rotation = new Vector3(0.0f, Time.deltaTime * rotationSpeed, 0.0f);
        //transform == position, rotation, scale for every game object
        transform.Rotate( rotation );
        //position = cannot change directly, have to set the position into a new vector

        //copy the current position
        Vector3 pos = transform.position;
        //alter the x
        pos.x = Mathf.Sin(Time.time) * 4.0f;
        //copy the altered position back into the transform
        transform.position = pos;
	}

    //called after all other updates (of all other objects)
    //something that depends on the physics of all other objects being updated
    void LateUpdate()
    {

    }
}
