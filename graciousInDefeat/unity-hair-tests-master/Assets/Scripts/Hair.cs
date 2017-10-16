using UnityEngine;

[ExecuteInEditMode]
public class Hair : MonoBehaviour {
    private static int MAXIMUM_INSTANCE_COUNT = 1023;
    public Mesh mesh;
    public Material material;
    public float hairLength = 20f;
    public float hairWidth = 0.02f;
    private int instanceCount;
    private Matrix4x4[] buffer;


    // Use this for initialization
    void Start () {
        Debug.Log("Creating GPU instances");
        MeshFilter meshRenderer = GetComponent<MeshFilter>();
        Mesh surfaceMesh = meshRenderer.mesh;

        Vector3[] surfaceVertices = surfaceMesh.vertices;
        //Vector3[] surfaceVerticesNormals = surfaceMesh.normals;
        instanceCount = surfaceMesh.vertexCount < MAXIMUM_INSTANCE_COUNT ? surfaceMesh.vertexCount : MAXIMUM_INSTANCE_COUNT;

        Debug.Log("Instance count: "+instanceCount);

        buffer = new Matrix4x4[instanceCount]; 

        for (int index = 0; index <instanceCount; index++) {
            Vector3 pos = surfaceVertices[index];
            Quaternion rotation = Quaternion.identity;
            Vector3 scale = new Vector3(hairWidth, hairLength, hairWidth);

            Matrix4x4 objectMatrix = gameObject.transform.localToWorldMatrix;
            // Offset the hair by the half length to 'anchor' the object at the top
            Vector3 translation = new Vector3(0, -(hairLength/2), 0);
            objectMatrix *= Matrix4x4.Translate(translation);

            Matrix4x4 theMatrix = Matrix4x4.TRS(pos, rotation, scale);
            objectMatrix *= theMatrix;
            buffer[index] = objectMatrix;
        }
	}
	
	// Update is called once per frame
	void Update () {
        Graphics.DrawMeshInstanced(mesh, 0, material, buffer, instanceCount);
	}
}
