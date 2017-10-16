using UnityEngine;

public class UsePointTopologyMeshMode : MonoBehaviour {

    [ContextMenu("Convert To Point Topology")]
    void ConvertToPointTopology() {
        Mesh mesh = GetComponent<MeshFilter>().mesh;
        int[] indices = new int[mesh.vertices.Length];
        for (int i = 0; i < indices.Length; i++) {
            indices[i] = i;
        }
        mesh.SetIndices(indices, MeshTopology.Points, 0);
    }

    // Use this for initialization
    void Start() {
        ConvertToPointTopology();
    }
}
