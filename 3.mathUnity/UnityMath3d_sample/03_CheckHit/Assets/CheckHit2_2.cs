using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CheckHit2_2 : MonoBehaviour {
    public Renderer rend;
    public Color colorNoHit = Color.cyan;
    public Color colorHit = Color.red;
    GameObject target;
    CapsuleBasic RefTarget;
    private float fVelocity = 0.1f;
    public float fRadius = 0.5f;

    // Use this for initialization
    void Start()
    {
        rend = GetComponent<Renderer>();
        target = GameObject.Find("Capsule2");
        RefTarget = target.GetComponent<CapsuleBasic>();
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        transform.position = new Vector3(transform.position.x + Input.GetAxis("Horizontal") * fVelocity,
                                         transform.position.y + Input.GetAxis("Vertical") * fVelocity,
                                         0.0f);
        Vector3 v3DeltaPos = transform.position - RefTarget.transform.position;
        float t = Vector3.Dot(RefTarget.v3Direction, v3DeltaPos) /
                  Vector3.SqrMagnitude(RefTarget.v3Direction);
        if (t < -1.0f) t = -1.0f;                     // tの下限
        if (t >  1.0f) t =  1.0f;                     // tの上限
        Vector3 v3MinPos = RefTarget.v3Direction * t + RefTarget.transform.position;   // 最小位置を与える座標
        float fDistSqr = Vector3.SqrMagnitude(v3MinPos - transform.position);     // 距離の２乗
        float ar = RefTarget.fRadius + fRadius;       // 両当たり範囲長の合計
        if (fDistSqr < ar * ar)
        {                       // ２乗のまま比較
            rend.material.color = colorHit;
        }
        else
        {
            rend.material.color = colorNoHit;
        }
    }
}
