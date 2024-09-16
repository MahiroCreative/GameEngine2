using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class prefabCookie : MonoBehaviour
{
    /*変数*/
    Vector3 _speed;

    void Start()
    {
        _speed = new Vector3(0,0.2f,0);
    }

    void Update()
    {
        //落下
        transform.position -= _speed;

        //ある程度落下したら消す
        if(transform.position.y < -16.0f)
        {
            Destroy(gameObject);
        }

    }
}
