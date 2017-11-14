using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PalmsManager : MonoBehaviour {

	public GameObject palmTreePrefab;
	List<GameObject> myPalms = new List<GameObject>();

	// Use this for initialization
	void Start () {

		for(int x = 0; x < 10; x++){
			for(int y = 0; y < 10; y++){
				for(int z = 0; z < 10; z++){
					myPalms.Add ( Instantiate(palmTreePrefab, new Vector3(x*.125f,y*.125f,z*.125f), Quaternion.identity));
				}
			}
		}

	}

	// Update is called once per frame
	void Update () {



		if (Input.GetKeyDown ("a")) {
			foreach (GameObject palmtree in myPalms) {
				palmtree.GetComponent<Rigidbody> ().isKinematic = false;
			}
		}else if (Input.GetKeyDown ("s")) {
			foreach (GameObject palmtree in myPalms) {
				palmtree.GetComponent<Rigidbody> ().isKinematic = true;
			}
		}

		RaycastHit hit;
		Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);

		if( /*Input.GetMouseButtonDown(0) &&*/  Physics.Raycast( ray, out hit) && hit.transform.tag == "Palm" ){
			foreach (GameObject sphere in myPalms) {
				Vector3 repel = sphere.transform.position-hit.transform.position ;
				float dist = repel.magnitude;
				if (dist < .5f) {
					repel.Normalize ();
//					Palm.GetComponent<Palm> ().addVelocity (repel*dist*.1f);
				}

			}
		}


	}
}
