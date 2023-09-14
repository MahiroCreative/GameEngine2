using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CheckHit1_1 : MonoBehaviour {
    public Renderer rend;
    public Color colorNoHit = Color.cyan;
    public Color colorHit = Color.red;
    GameObject target;
    private float fVelocity = 0.1f;

    // Use this for initialization
    void Start () {
        rend = GetComponent<Renderer>();
        target = GameObject.Find("Cube2");
    }

    // Update is called once per frame
    void FixedUpdate() {
        transform.position = new Vector3(transform.position.x + Input.GetAxis("Horizontal") * fVelocity,
                                         transform.position.y + Input.GetAxis("Vertical"  ) * fVelocity,
                                         0.0f);
        if ((Mathf.Abs(transform.position.x - target.transform.position.x) < 1.0f) &&
            (Mathf.Abs(transform.position.y - target.transform.position.y) < 1.0f) &&
            (Mathf.Abs(transform.position.z - target.transform.position.z) < 1.0f))
        {
            rend.material.color = colorHit;
        }
        else
        {
            rend.material.color = colorNoHit;
        }
    }
}
