using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GenCubeScript2 : MonoBehaviour {
    public GameObject cube;
    private const int nObjCount = 20;
    private const float fInterval = 0.5f;
    public Renderer rend;

    // Use this for initialization
    void Start()
    {
        GameObject RootObje = GameObject.Find("Cube");          // ルートオブジェクト
        Vector3 v3Position = new Vector3(-5.0f, 0.0f, 0.0f);    // 位置
        RootObje.transform.position = v3Position;
        RootObje.transform.parent = null;                       // ルートに親なし
        GameObject lastGameObje = RootObje;
        for (int i = 1; i <= nObjCount; i++)
        {
            GameObject GameObje = Instantiate(cube);            // オブジェクト生成
            v3Position.x += fInterval;
            GameObje.transform.position = v3Position;
            GameObje.transform.parent = lastGameObje.transform; // 親
            Transform4_1 ScRef = GameObje.GetComponent<Transform4_1>();
            ScRef.nDepth = i;                                   // 階層深さ
            lastGameObje = GameObje;
        }
    }

    // Update is called once per frame
    void Update()
    {
    }
}
