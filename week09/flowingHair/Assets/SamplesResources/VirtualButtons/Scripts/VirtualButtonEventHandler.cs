/*============================================================================== 
 Copyright (c) 2016-2017 PTC Inc. All Rights Reserved.
 
 Copyright (c) 2012-2015 Qualcomm Connected Experiences, Inc. All Rights Reserved. 
 * ==============================================================================*/
using UnityEngine;
using Vuforia;

/// <summary>
/// This class implements the IVirtualButtonEventHandler interface and
/// contains the logic to start animations depending on what 
/// virtual button has been pressed.
/// </summary>
public class VirtualButtonEventHandler : MonoBehaviour,
                                         IVirtualButtonEventHandler
{
    #region PUBLIC_MEMBERS
    public Material m_VirtualButtonMaterial;
    public Material m_VirtualButtonMaterialPressed;
    #endregion // PUBLIC_MEMBERS

    #region PRIVATE_MEMBERS
    VirtualButtonBehaviour[] virtualBtnBehaviours;
    #endregion // PRIVATE_MEMBERS

    #region MONOBEHAVIOUR_METHODS
    void Start()
    {
        // Register with the virtual buttons TrackableBehaviour
        virtualBtnBehaviours = GetComponentsInChildren<VirtualButtonBehaviour>();

        for (int i = 0; i < virtualBtnBehaviours.Length; ++i)
        {
            virtualBtnBehaviours[i].RegisterEventHandler(this);
        }
    }

    #endregion // MONOBEHAVIOUR_METHODS


    #region PUBLIC_METHODS
    /// <summary>
    /// Called when the virtual button has just been pressed:
    /// </summary>
    public void OnButtonPressed(VirtualButtonBehaviour vb)
    {
        Debug.Log("OnButtonPressed: " + vb.VirtualButtonName);

        SetVirtualButtonMaterial(m_VirtualButtonMaterialPressed);

        // Add the material corresponding to this virtual button
        // to the active material list:
        switch (vb.VirtualButtonName)
        {
            case "wave":
                // Start Astronaut waving animation
                GetComponentInChildren<Animator>().SetBool("IsWaving", true);
                break;

            case "scan":
                // Start Drone scanning animation
                Drone drone = GetComponentInChildren<Drone>();
                drone.AnimEvt_StartScanning();
                break;

            case "oxygen":
                // Start Oxygen Tank display animation
                GetComponentInChildren<Animator>().SetBool("IsDetailOn", true);
                break;

            case "fissure":
                // Change fissure color
                var fissureGradient = GetComponentInChildren<ParticleSystem>().colorOverLifetime;
                fissureGradient.enabled = true;

                // Create dark red to black gradient
                Gradient gradient = new Gradient();
                gradient.SetKeys(new GradientColorKey[] {
                    new GradientColorKey(new Color(0.6f, 0f, 0f), 0.0f),
                    new GradientColorKey(Color.black, 0.7f) },
                    new GradientAlphaKey[] { new GradientAlphaKey(1.0f, 0.0f),
                    new GradientAlphaKey(0.5f, 1.0f) });

                fissureGradient.color = gradient;
                break;
        }
    }

    /// <summary>
    /// Called when the virtual button has just been released:
    /// </summary>
    public void OnButtonReleased(VirtualButtonBehaviour vb)
    {
        Debug.Log("OnButtonReleased: " + vb.VirtualButtonName);

        SetVirtualButtonMaterial(m_VirtualButtonMaterial);

        switch (vb.VirtualButtonName)
        {
            case "wave":
                // Stop Astronaut waving animation
                GetComponentInChildren<Animator>().SetBool("IsWaving", true);
                break;

            case "scan":
                // Stop Drone scanning animation
                Drone drone = GetComponentInChildren<Drone>();
                drone.AnimEvt_StopScanning();
                break;

            case "oxygen":
                // Hide Oxygen Tank display
                GetComponentInChildren<Animator>().SetBool("IsDetailOn", false);
                break;

            case "fissure":
                // Revert Fissure color
                var fissureGradient = GetComponentInChildren<ParticleSystem>().colorOverLifetime;
                fissureGradient.enabled = false;
                break;
        }
    }

    #endregion //PUBLIC_METHODS

    #region PRIVATE_METHODS
    void SetVirtualButtonMaterial(Material material)
    {
        // Set the Virtual Button material
        for (int i = 0; i < virtualBtnBehaviours.Length; ++i)
        {
            if (material != null)
            {
                virtualBtnBehaviours[i].GetComponent<MeshRenderer>().sharedMaterial = material;
            }
        }
    }
    #endregion // PRIVATE METHODS
}
