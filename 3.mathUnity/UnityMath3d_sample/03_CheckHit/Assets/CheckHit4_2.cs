using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CheckHit4_2 : MonoBehaviour {
    public Renderer rend;
    public Color colorNoHit = Color.cyan;
    public Color colorHit = Color.red;
    GameObject target;
    private const float fVelocity = 0.1f;

    // Use this for initialization
    void Start()
    {
        transform.position = new Vector3(-2.0f, -2.5f, 0.0f);
        rend = GetComponent<Renderer>();
        target = GameObject.Find("Plane");
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        transform.position = new Vector3(transform.position.x + Input.GetAxis("Horizontal") * fVelocity,
                                         transform.position.y,
                                         transform.position.z + Input.GetAxis("Vertical") * fVelocity);
        MakePolygon TargetPoly;
        Vector3 v3TriVec0, v3TriVec1, v3TriVec2;
        Vector3 v3HitVec0, v3HitVec1, v3HitVec2;
        float fCross0, fCross1, fCross2;
        float fDot;
        bool bHit;
        TargetPoly = target.GetComponent<MakePolygon>();

        // 三角形サイクルベクトル
        v3TriVec0 = TargetPoly.positions[1] - TargetPoly.positions[0];
        v3TriVec1 = TargetPoly.positions[2] - TargetPoly.positions[1];
        v3TriVec2 = TargetPoly.positions[0] - TargetPoly.positions[2];
        // サイクルベクトル単位化
        v3TriVec0.Normalize();
        v3TriVec1.Normalize();
        v3TriVec2.Normalize();
        // 三角形頂点からターゲットへのベクトル
        v3HitVec0 = transform.position - TargetPoly.positions[0];
        v3HitVec1 = transform.position - TargetPoly.positions[1];
        v3HitVec2 = transform.position - TargetPoly.positions[2];
        // それぞれの外積(のy成分)
        fCross0 = v3TriVec0.z * v3HitVec0.x - v3TriVec0.x * v3HitVec0.z;
        fCross1 = v3TriVec1.z * v3HitVec1.x - v3TriVec1.x * v3HitVec1.z;
        fCross2 = v3TriVec2.z * v3HitVec2.x - v3TriVec2.x * v3HitVec2.z;
        bHit = false;
        if (fCross0 >= 0.0f)
        {
            if ((fCross1 >= 0.0f) && (fCross2 >= 0.0f))
            {
                bHit = true;
            }
        }
        else
        {
            if ((fCross1 < 0.0f) && (fCross2 < 0.0f))
            {
                bHit = true;
            }
        }

        if (bHit)
        {
            // プレイヤー位置制御
            if ((Mathf.Abs(fCross0) <= Mathf.Abs(fCross1)) &&
                 (Mathf.Abs(fCross0) <= Mathf.Abs(fCross2)))
            {
                // 辺０に一番近い
                fDot = Vector3.Dot(v3TriVec0, v3HitVec0);
                transform.position = new Vector3(v3TriVec0.x * fDot + TargetPoly.positions[0].x,
                                                 transform.position.y,
                                                 v3TriVec0.z * fDot + TargetPoly.positions[0].z);
            }
            else
            {
                if (Mathf.Abs(fCross1) <= Mathf.Abs(fCross2))
                {
                    // 辺１に一番近い
                    fDot = Vector3.Dot(v3TriVec1, v3HitVec1);
                    transform.position = new Vector3(v3TriVec1.x * fDot + TargetPoly.positions[1].x,
                                                     transform.position.y,
                                                     v3TriVec1.z * fDot + TargetPoly.positions[1].z);
                }
                else
                {
                    // 辺２に一番近い
                    fDot = Vector3.Dot(v3TriVec2, v3HitVec2);
                    transform.position = new Vector3(v3TriVec2.x * fDot + TargetPoly.positions[2].x,
                                                     transform.position.y,
                                                     v3TriVec2.z * fDot + TargetPoly.positions[2].z);
                }
            }
        }
        if (bHit)
        {
            rend.material.color = colorHit;
        }
        else
        {
            rend.material.color = colorNoHit;
        }
    }
}
