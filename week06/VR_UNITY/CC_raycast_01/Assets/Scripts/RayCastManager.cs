using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RayCastManager : MonoBehaviour {

    Transform mainCam;
    public GameObject particlePrefab;
    public GameObject drawPrefab;

	// Use this for initialization
	void Start () {
        //camera.main will give you the main cam in the scene
        mainCam = Camera.main.transform;		
	}
	
	// Update is called once per frame
	void Update () {

        //store the collision information
        RaycastHit hit;
        var randomInt = Random.Range(0, 5);

        //gonna return a true or false collided
        //out hit: passes in out hit object, then keeps a reference to it
        bool isHit = Physics.Raycast(mainCam.position, mainCam.forward, out hit);
        //when it hits the object tagged "fjkhfos":
        if (isHit && hit.collider.tag == "HitObject")
        {
            Debug.Log("Collision!!");

            //our goal: disable kinematic on rigidbody
            //  hit.collider.GetComponent<Rigidbody>().isKinematic = false;

            //instantiate prefab at colider position:
            //instantiate has a lot of ways to do it: this way it also requires it's original angle/rotation
            //quaternion.id is a standard angle/rotation thing

            //Instantiate( particlePrefab, hit.collider.transform.position, Quaternion.identity );
            //Instantiate(drawPrefab, new Vector3(hit.point.x, hit.point.y, hit.point.z + Mathf.PerlinNoise(Time.time * 50, 0.0F)), Quaternion.identity);

            // destroy the game object we collided with:
            //Destroy( hit.collider.gameObject );
        }

        if (isHit)
        {
            Instantiate(drawPrefab, new Vector3(hit.point.x, hit.point.y, hit.point.z + Mathf.PerlinNoise(Time.time * 250, 0.0F)), Quaternion.identity);
        }

        //this was just for debug:
        //make a serpatae variable, to make ray lower (because it draws it at eyelevel for FBS cont.):
            Vector3 pos = new Vector3(
            mainCam.position.x,
            mainCam.position.y - .25F,
            mainCam.position.z
            ); 
        Debug.DrawRay( pos, mainCam.forward * 200, Color.green );
	}
}
