using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Transform1_4 : MonoBehaviour {
    public Renderer rend;
    public Color colorCube = Color.red;
    private float fAngle2 = 0.0f;
    Vector3 v3InitialPos;                       // 初期位置
    Quaternion qInitialRot;                     // 初期回転

    // Use this for initialization
    void Start()
    {
        float fXAbs, fYAbs, fZAbs;

        rend = GetComponent<Renderer>();

        fXAbs = Mathf.Abs(transform.position.x);
        fYAbs = Mathf.Abs(transform.position.y);
        fZAbs = Mathf.Abs(transform.position.z);

        if ((fXAbs > fYAbs) && (fXAbs > fZAbs))
        {
            colorCube = Color.magenta;
        }
        else
        {
            if (fYAbs > fZAbs)
            {
                colorCube = Color.cyan;
            }
            else
            {
                colorCube = Color.yellow;
            }
        }
        v3InitialPos = transform.position;
        qInitialRot = transform.rotation;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        // 回転の行列1
        float fAngle1 = 2.0f * Mathf.PI * ((Time.time / 10.0f) % 1); // 角度
        Matrix4x4 matTransform1 = Matrix4x4.identity;                      // 単位行列
        matTransform1.m00 =  Mathf.Cos(fAngle1); matTransform1.m02 = Mathf.Sin(fAngle1);
        matTransform1.m20 = -Mathf.Sin(fAngle1); matTransform1.m22 = Mathf.Cos(fAngle1);
        // 回転の行列2
        fAngle2 += Input.GetAxis("Vertical") * 0.05f;                      // 角度
        Matrix4x4 matTransform2 = Matrix4x4.identity;                      // 単位行列
        matTransform2.m11 = Mathf.Cos(fAngle2); matTransform2.m12 = -Mathf.Sin(fAngle2);
        matTransform2.m21 = Mathf.Sin(fAngle2); matTransform2.m22 =  Mathf.Cos(fAngle2);
        Matrix4x4 matTransform = matTransform2 * matTransform1;
        //Matrix4x4 matTransform = matTransform1 * matTransform2;
        transform.position = matTransform * v3InitialPos;               // 変換
        transform.rotation = qInitialRot;                               // 回転初期化
        transform.Rotate(0.0f, fAngle1 * 360.0f / (2.0f * Mathf.PI), 0.0f, Space.World);
        transform.Rotate(fAngle2 * 360.0f / (2.0f * Mathf.PI), 0.0f, 0.0f, Space.World);
        //transform.Rotate(fAngle2 * 360.0f / (2.0f * Mathf.PI), 0.0f, 0.0f, Space.World);
        //transform.Rotate(0.0f, fAngle1 * 360.0f / (2.0f * Mathf.PI), 0.0f, Space.World);
        rend.material.color = colorCube;
    }
}
