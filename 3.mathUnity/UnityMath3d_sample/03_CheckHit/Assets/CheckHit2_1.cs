using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CheckHit2_1 : MonoBehaviour {
    public Renderer rend;
    public Color colorNoHit = Color.cyan;
    public Color colorHit = Color.red;
    GameObject target;
    private float fVelocity = 0.1f;

    // Use this for initialization
    void Start()
    {
        rend = GetComponent<Renderer>();
        target = GameObject.Find("Sphere2");
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        transform.position = new Vector3(transform.position.x + Input.GetAxis("Horizontal") * fVelocity,
                                         transform.position.y + Input.GetAxis("Vertical") * fVelocity,
                                         0.0f);
        Vector3 v3Delta = transform.position - target.transform.position;
        float fDistanceSq = v3Delta.x * v3Delta.x + v3Delta.y * v3Delta.y + v3Delta.z * v3Delta.z;
        if (fDistanceSq < (1.0f * 1.0f))
        {
            rend.material.color = colorHit;
        }
        else
        {
            rend.material.color = colorNoHit;
        }
    }
}
