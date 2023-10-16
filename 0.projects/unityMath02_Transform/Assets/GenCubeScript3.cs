using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GenCubeScript3 : MonoBehaviour {
    public GameObject cube;
    private const int nBaseObje = 10;
    private const int nBranchObje = 10;
    private const float fInterval = 0.5f;
    private Vector3 v3Interval1 = new Vector3(0.5f,  0.5f, 0.0f);
    private Vector3 v3Interval2 = new Vector3(0.5f, -0.5f, 0.0f);
    public Renderer rend;

    // Use this for initialization
    void Start()
    {
        int i;
        GameObject GameObje, lastGameObje;              // 生成オブジェクト、ひとつ前の生成オブジェクト
        Vector3 v3Position = new Vector3(-2.0f, 0.0f, 0.0f);

        GameObject DisappObje = GameObject.Find("Plane");  // 隠すオブジェクト
        if (DisappObje)
        {
            DisappObje.SetActive(false);
        }
        GameObject RootObje = GameObject.Find("Cube");  // ルートオブジェクト
        RootObje.transform.position = v3Position;
        RootObje.transform.parent = null;
        lastGameObje = RootObje;
        int nDepth = 1;
        for (i = 1; i <= nBaseObje; i++)
        {
            v3Position.x += fInterval;
            GameObje = MyInstantiate(v3Position, lastGameObje, nDepth);
            lastGameObje = GameObje;
            nDepth++;
        }
        GameObject lastGameObje1 = lastGameObje;
        GameObject lastGameObje2 = lastGameObje;   // ひとつ前の生成オブジェクト
        Vector3 v3Position1 = v3Position;
        Vector3 v3Position2 = v3Position;
        for (i = 1; i <= nBranchObje; i++)
        {
            v3Position1 += v3Interval1;
            GameObje = MyInstantiate(v3Position1, lastGameObje1, nDepth);
            lastGameObje1 = GameObje;
            v3Position2 += v3Interval2;
            GameObje = MyInstantiate(v3Position2, lastGameObje2, nDepth);
            lastGameObje2 = GameObje;
            nDepth++;
        }
    }

    // カスタムインスタンス化
    GameObject MyInstantiate(Vector3 v3GenPos, GameObject GenParent, int nDepth)
    {
        GameObject GameObje = Instantiate(cube);
        GameObje.transform.position = v3GenPos;
        GameObje.transform.parent = GenParent.transform;
        Transform4_2 ScRef = GameObje.GetComponent<Transform4_2>();
        ScRef.nDepth = nDepth;
        ScRef.v3BasePos = GameObje.transform.position - GameObje.transform.parent.position;

        return GameObje;
    }

    // Update is called once per frame
    void Update()
    {
    }
}
