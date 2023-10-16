using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CheckHit3_1 : MonoBehaviour {
    public Renderer rend;
    public Color colorNoHit = Color.cyan;
    public Color colorHit = Color.red;
    public Color colorPararrelNoHit = Color.yellow;
    public Color colorPararrelHit = Color.magenta;
    GameObject target;
    CapsuleBasic RefTarget;
    private float fVelocity = 0.1f;
    public Vector3 v3Direction;                 // 方向ベクトル
    public float fRadius = 0.5f;
    private Quaternion qRot;

    // Use this for initialization
    void Start()
    {
        rend = GetComponent<Renderer>();
        target = GameObject.Find("Capsule2");
        RefTarget = target.GetComponent<CapsuleBasic>();
        target.transform.position = new Vector3(-1.0f, 2.0f, 0.3f);
        qRot = Quaternion.AngleAxis(30.0f, new Vector3(1.0f, 1.0f, 1.0f));
        v3Direction = new Vector3(0.0f, 0.5f, 0.0f);
        v3Direction = qRot * v3Direction;
        transform.rotation = qRot;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        float s, t;
        transform.position = new Vector3(transform.position.x + Input.GetAxis("Horizontal") * fVelocity,
                                         transform.position.y + Input.GetAxis("Vertical") * fVelocity,
                                         0.0f);
        Vector3 v3DeltaPos = RefTarget.transform.position - transform.position;
        Vector4 v4DeltaPos = new Vector4(v3DeltaPos.x, v3DeltaPos.y, v3DeltaPos.z, 0.0f);
        Vector3 v3Normal = Vector3.Cross(RefTarget.v3Direction, v3Direction);
        bool bParallel = false;
        if (v3Normal.sqrMagnitude < 0.001f) bParallel = true;
        if (!bParallel)
        {
            Matrix4x4 matSolve = Matrix4x4.identity;
            matSolve.SetColumn(0, new Vector4(v3Direction.x, v3Direction.y, v3Direction.z, 0.0f));
            matSolve.SetColumn(1, new Vector4(-RefTarget.v3Direction.x,
                                              -RefTarget.v3Direction.y,
                                              -RefTarget.v3Direction.z, 0.0f));
            matSolve.SetColumn(2, new Vector4(v3Normal.x, v3Normal.y, v3Normal.z, 0.0f));
            matSolve = matSolve.inverse;                        // 逆行列
            s = Vector4.Dot(matSolve.GetRow(0), v4DeltaPos);
            t = Vector4.Dot(matSolve.GetRow(1), v4DeltaPos);
        }
        else
        {
            s = Vector3.Dot(v3Direction, v3DeltaPos) /
                Vector3.SqrMagnitude(v3Direction);
            t = Vector3.Dot(RefTarget.v3Direction, -v3DeltaPos) /
                Vector3.SqrMagnitude(RefTarget.v3Direction);
        }
        if (s < -1.0f) s = -1.0f;                    // sの下限
        if (s >  1.0f) s =  1.0f;                    // sの上限
        if (t < -1.0f) t = -1.0f;                    // tの下限
        if (t >  1.0f) t =  1.0f;                    // tの上限
        Vector3 v3MinPos1 = v3Direction * s + transform.position;
        Vector3 v3MinPos2 = RefTarget.v3Direction * t + RefTarget.transform.position;
        float fDistSqr = Vector3.SqrMagnitude(v3MinPos1 - v3MinPos2);
        float ar = RefTarget.fRadius + fRadius;
        if (fDistSqr < ar * ar)
        {                       // ２乗のまま比較
            if (!bParallel)
            {
                rend.material.color = colorHit;
            }
            else
            {
                rend.material.color = colorPararrelHit;
            }
        }
        else
        {
            if (!bParallel)
            {
                rend.material.color = colorNoHit;
            }
            else
            {
                rend.material.color = colorPararrelNoHit;
            }
        }
    }
}
