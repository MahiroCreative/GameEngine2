using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CheckHit1_2 : MonoBehaviour {
    public Renderer rend;
    public Color colorNoHit = Color.cyan;
    public Color colorHit = Color.red;
    GameObject target;
    private float fVelocity = 0.1f;

    // Use this for initialization
    void Start()
    {
        rend = GetComponent<Renderer>();
        target = GameObject.Find("Cube2");
        transform.localScale = new Vector3(2.0f, 1.0f, 1.0f);           // 自身のスケール
        target.transform.localScale = new Vector3(1.5f, 2.0f, 1.0f);    // 相手のスケール
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        transform.position = new Vector3(transform.position.x + Input.GetAxis("Horizontal") * fVelocity,
                                         transform.position.y + Input.GetAxis("Vertical") * fVelocity,
                                         0.0f);
        Vector3 v3SubAbs = transform.position - target.transform.position;
        v3SubAbs = new Vector3(Mathf.Abs(v3SubAbs.x), Mathf.Abs(v3SubAbs.y), Mathf.Abs(v3SubAbs.z));
        Vector3 v3AddScale = ( transform.localScale + target.transform.localScale ) / 2.0f;
        if ((v3SubAbs.x < v3AddScale.x) &&
            (v3SubAbs.y < v3AddScale.y) &&
            (v3SubAbs.z < v3AddScale.z))
        {
            rend.material.color = colorHit;
        }
        else
        {
            rend.material.color = colorNoHit;
        }
    }
}
