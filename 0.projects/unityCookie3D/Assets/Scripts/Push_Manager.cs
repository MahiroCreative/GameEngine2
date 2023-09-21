using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Push_Manager : MonoBehaviour
{
    /*�J�E���g�ϐ�*/
    float _count = 0;
    float _deltaGen = 0;
    float _hand = 0;
    float _grandma = 0;
    float _factory = 0;

    /*�^�C�}�[*/
    float _timer = 0;

    /*�ʒu*/
    float _handPos=-8;
    float _grandmaPos = -8;
    float _factoryPos = -8;

    /*�I�u�W�F�N�g�ƃR���|�[�l���g�ϐ�*/
    GameObject _obj;
    GameObject _grandmaObj;
    GameObject _handObj;
    GameObject _factoryObj;
    Transform _cookieTrans;
    Text _countText;
    Text _deltaText;

    /*�N�b�L�[�̉�]*/
    Vector3 _axis;//��]��
    Quaternion _delQ;//��]�x����

    /*�g��k��*/
    bool _bigFlag=false;
    Vector3 _minScale;
    Vector3 _delScale;

    void Start()
    {
        /*�R���|�[�l���g�擾*/
        _cookieTrans = GameObject.Find("MainCookie").GetComponent<Transform>();
        _countText = GameObject.Find("countText").GetComponent<Text>();
        _deltaText = GameObject.Find("deltaCountText").GetComponent<Text>();

        /*prefabCookie�̎擾*/
        _obj = (GameObject)Resources.Load("prefabCookie");
        _handObj = (GameObject)Resources.Load("preHand");
        _grandmaObj = (GameObject)Resources.Load("preGrandma");
        _factoryObj = (GameObject)Resources.Load("preFactory");

        /*�N�b�L�[�̉�]*/
        //��]���̍쐬
        _axis = new Vector3(0,0,1.0f);
        //��]�N�I�[�^�j�I���̍쐬
        _delQ = Quaternion.AngleAxis(0.4f, _axis);

        /*�g��k��*/
        _minScale = new Vector3(1.6f,1.6f,1.6f);
        _delScale = new Vector3(0.02f,0.02f,0.02f);
    }

    void FixedUpdate()
    {
        //�펞��]
        _cookieTrans.rotation = _delQ * _cookieTrans.rotation;

        //�N���b�N��Ɋg��
        if(_bigFlag && _cookieTrans.localScale.x <= 2.0f)
        {
            _cookieTrans.localScale += _delScale;
        }

        //�J�E���g�̍X�V
        _deltaGen = _hand + _grandma + _factory;
        _count += _deltaGen;

        //�J�E���g�̍X�V�\��
        _countText.text = ((int)_count).ToString();

        //delta�̍X�V�\��
        _deltaText.text = ((int)(_deltaGen *�@51)).ToString();

        //delta��������ȏ�ɂȂ�����N�b�L�[��K���ɍ~�炷
        FallingCookie(_deltaGen);
    }



    /*���상�\�b�h*/
    /// <summary>
    /// _deltaGen(�b�Ԃ̃N�b�L�[�̐�����)�̒l�ɍ��킹�āA
    /// �����ŗ������Ă���N�b�L�[�̗ʂ𑝌�������B
    /// </summary>
    /// <param name="deltaGen"></param>
    public void FallingCookie(float deltaGen)
    {
        if (deltaGen > 3.2f)
        {
            //timer
            _timer += Time.deltaTime;

            if (_timer > 0.04f)
            {
                //��������
                float x = Random.Range(-20.0f, 20.0f);
                float z = Random.Range(12.0f, 24.0f);
                //�C���X�^���X����
                Instantiate(_obj, new Vector3(x, 16.0f, z), Quaternion.Euler(0, 180, 0));

                //timer�̏�����
                _timer = 0;
            }
        }
        else if (deltaGen > 0.80f)
        {
            //timer
            _timer += Time.deltaTime;

            if (_timer > 0.2f)
            {
                //��������
                float x = Random.Range(-20.0f, 20.0f);
                float z = Random.Range(12.0f, 24.0f);
                //�C���X�^���X����
                Instantiate(_obj, new Vector3(x, 16.0f, z), Quaternion.Euler(0, 180, 0));

                //timer�̏�����
                _timer = 0;
            }

        }
        else if (deltaGen > 0.08f)
        {
            //timer
            _timer += Time.deltaTime;

            if (_timer > 1.6f)
            {
                //��������
                float x = Random.Range(-20.0f, 20.0f);
                float z = Random.Range(12.0f, 24.0f);
                //�C���X�^���X����
                Instantiate(_obj, new Vector3(x, 16.0f, z), Quaternion.Euler(0, 180, 0));

                //timer�̏�����
                _timer = 0;
            }
        }
        else if (deltaGen > 0.01f)
        {
            //timer
            _timer += Time.deltaTime;

            if (_timer > 8.0f)
            {
                //��������
                float x = Random.Range(-20.0f, 20.0f);
                float z = Random.Range(12.0f, 24.0f);
                //�C���X�^���X����
                Instantiate(_obj, new Vector3(x, 16.0f, z), Quaternion.Euler(0, 180, 0));

                //timer�̏�����
                _timer = 0;
            }
        }
    }

    /*�{�^�����\�b�h*/
    public void onClick()
    {
        //�k��
        _cookieTrans.localScale = _minScale; 
        //�g��t���Oon
        _bigFlag = true;
        //�J�E���g�̍X�V
        _count += 1.0f;

        //��������
        float x = Random.Range(-20.0f,20.0f);
        float z = Random.Range(12.0f,24.0f);
        //�C���X�^���X����(�N�b�L�[����)
        Instantiate(_obj,new Vector3(x,16.0f,z),Quaternion.Euler(0,180,0));
    }

    public void handButton()
    {
        if(_count >= 8)
        {
            _count = _count - 8;
            _hand = _hand + 0.02f;
            //�C���X�^���X����(hand����)
            Instantiate(_handObj, new Vector3(_handPos, 1.6f, 1), Quaternion.identity);
            //�����ʒu�����炷
            _handPos += 0.8f;
        }

    }
    public void granmaButton()
    {
        if(_count >= 80)
        {
            _count = _count - 80;
            _grandma = _grandma + 0.1f;
            //�C���X�^���X����(grandma����)
            Instantiate(_grandmaObj, new Vector3(_grandmaPos, 0, 1), Quaternion.identity);
            //�����ʒu�����炷
            _grandmaPos += 0.8f;
        }

    }
    public void factoryButton()
    {
        if(_count > 800)
        {
            _count = _count - 800;
            _factory = _factory + 1.0f;
            //�C���X�^���X����(factory����)
            Instantiate(_factoryObj, new Vector3(_factoryPos, -1.6f, 1), Quaternion.identity);
            //�����ʒu�����炷
            _factoryPos += 0.8f;
        }

    }
}
