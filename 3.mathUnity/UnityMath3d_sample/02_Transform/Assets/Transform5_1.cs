using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Transform5_1 : MonoBehaviour {
    public Renderer rend;
    public Color colorCube = Color.red;
    private float fAngle = 0.0f;

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
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        Quaternion qRot;
        Vector3 v3Axis = new Vector3(1.0f, 1.0f, 1.0f);

        fAngle = 2.0f * Mathf.PI * Time.deltaTime / 10.0f;          // 角度
        qRot = Quaternion.AngleAxis(fAngle * Mathf.Rad2Deg, v3Axis); // 回転のクォータニオン

        // クォータニオンによる回転
        transform.position = qRot * transform.position;            // 位置
        transform.rotation = qRot * transform.rotation;            // 回転
        rend.material.color = colorCube;
    }
}
