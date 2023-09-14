using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Transform4_2 : MonoBehaviour {
    Quaternion qInitialRot;                     // 初期回転
    public int nDepth = 0;
    public Vector3 v3BasePos = new Vector3( 2.0f, 0.0f, 0.0f );

    // Use this for initialization
    void Start()
    {
        qInitialRot = transform.rotation;
        float fBright = (20.0f - (float)nDepth) / 20.0f;
        GetComponent<Renderer>().material.color = new Color(0.9f + fBright * 0.1f, fBright, 0.7f + fBright * 0.3f);
    }
        // Update is called once per frame
    void Update()
    {

    }

    // Update is called once per frame
    void FixedUpdate()
    {
        if (transform.parent)
        {
            float fPosAngle = nDepth * 2.0f * Mathf.PI / 25.0f *
                              Mathf.Sin(2.0f * Mathf.PI * ((Time.time / 6.0f) % 1));
            Vector3 v3RotAxis = new Vector3(-0.6f, -0.5f, 0.3f);
            Quaternion qRot = Quaternion.AngleAxis(fPosAngle * 360.0f / (2.0f * Mathf.PI), v3RotAxis);
            Vector3 v3RelPos = qRot * v3BasePos;
            transform.position = transform.parent.position + v3RelPos;
            transform.LookAt(transform.parent.position, new Vector3(0.0f, 1.0f, 0.0f));
        }
    }
}
