using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TrailRenderer : MonoBehaviour {

    public float startWidth;
    public float endWidth;
    public Gradient colorGradient;
    void start()
    {
        float alpha = 0.2f;
        Gradient gradient = new Gradient();
        //gradient.SetKeys(
        //    new GradientColorKey[] {new GradientColorKey(Color.green, 0.0f), new GradientColorKey(Color.red, 1.0f)}'
        //    new GradientAlphaKey[] { new GradientAlphaKey(alpha, 0.0f), new GradientAlphaKey(alpha, 1.0f) }
        //    );
        //TrailRenderer.colorGradient = gradient;
    }

	// Update is called once per frame
	void Update () {
		if(((Input.touchCount > 0 && Input.GetTouch(0).phase == TouchPhase.Moved)
            || Input.GetMouseButton(0)))
        {
            Plane objPlane = new Plane(Camera.main.transform.forward * -1, this.transform.position);


            Ray mRay = Camera.main.ScreenPointToRay(Input.mousePosition);
            float rayDistance;
            if (objPlane.Raycast(mRay, out rayDistance))
                this.transform.position = mRay.GetPoint(rayDistance);
        }

    }
}
