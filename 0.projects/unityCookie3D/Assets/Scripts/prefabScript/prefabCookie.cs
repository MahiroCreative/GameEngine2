using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class prefabCookie : MonoBehaviour
{
    /*�ϐ�*/
    Vector3 _speed;

    void Start()
    {
        _speed = new Vector3(0,0.2f,0);
    }

    void Update()
    {
        //����
        transform.position -= _speed;

        //������x�������������
        if(transform.position.y < -16.0f)
        {
            Destroy(gameObject);
        }

    }
}
