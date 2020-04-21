using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Xml;
using Assets.Client.Data;
using Assets.Client.Parser;

public class Test : MonoBehaviour
{
    public Object a;
    private LinkedList<WzObject> listWzObject ;
    // Start is called before the first frame update
    void Start()
    {
        listWzObject = new LinkedList<WzObject>();
        StartCoroutine(Loading());

    }
    void ParsingChildNodes(WzObject wzObject ,XmlNodeList childnodelist)
    {
            foreach (XmlNode childnode in childnodelist)
            {
            XmlElement xmlElement = (XmlElement)childnode;
            if (childnode.HasChildNodes)
            {

                print("추가 자식노드 " + childnode.Attributes[0].Value + " 를 파싱합니다");
                wzObject.AddChild(new WzObjectChild(childnode.Attributes[0].Value, wzObject));
                
                ParsingChildNodes(wzObject.getChild(childnode.Attributes[0].Value), childnode.ChildNodes);
            }
            else
            {

                //   print(xmlElement.Name + "자료형의"  + xmlElement.Attributes[0].Value  + " 데이터" );
                if (xmlElement.Name == "vector")
                {
                    wzObject.AddProperty(xmlElement.Attributes[0].Value, new MapleData(MapleDataType.VECTOR, new Vector2(int.Parse(xmlElement.Attributes[1].Value), int.Parse(xmlElement.Attributes[2].Value))));
                    //string log = xmlElement.Name + " " + xmlElement.Attributes[0].Value + " = {";
                    //for (int i = 1; i < xmlElement.Attributes.Count; i++)
                    //{
                    //    log += xmlElement.Attributes[i].Value;
                    //    if (i == 1) log += " , ";
                    //}
                    //print(log + "}");
                }
                else if (xmlElement.Name == "string" || xmlElement.Name == "uol")
                {
                    wzObject.AddProperty(xmlElement.Attributes[0].Value, new MapleData(MapleDataType.STRING, xmlElement.Attributes[1].Value));
                    // for (int i = 1; i < xmlElement.Attributes.Count; i++)
                    //  {
                    // print(xmlElement.Name + " " + xmlElement.Attributes[0].Value + " = " +  xmlElement.Attributes[i].Value);
                    //}

                }
                else
                {
                    if (xmlElement.Attributes.Count >= 2)
                    {
                        try
                        {
                            wzObject.AddProperty(xmlElement.Attributes[0].Value, new MapleData(MapleDataType.INT, int.Parse(xmlElement.Attributes[1].Value)));
                        }
                        catch
                        {

                            print("ERROR : " + xmlElement.Name + " " + xmlElement.Attributes[1].Value);
                        }
                    }
                }

            }
            }
    }
    IEnumerator Loading()
    {
        TextAsset textAsset = (TextAsset)a;
        Debug.Log(textAsset);
        XmlDocument xmlDoc = new XmlDocument();

        xmlDoc.LoadXml(textAsset.text);

        print("노드의 개수 : " + xmlDoc.ChildNodes.Item(1).ChildNodes.Count);
        foreach (XmlNode node in xmlDoc.ChildNodes.Item(1).ChildNodes)
        {
            yield return null;
            print("자식노드 " + node.Attributes[0].Value + " 를 파싱합니다");
            WzObject obj = new WzObject(node.Attributes[0].Value);
            listWzObject.AddLast(obj);
            XmlNodeList childnodelist = node.ChildNodes;
            ParsingChildNodes(obj, childnodelist);
            print("========================================");

        }
        Debug.ClearDeveloperConsole();
        print("파싱완료 데이터를 출력합니다.");
        foreach (var data in listWzObject)
        {
           StartCoroutine( PrintNode(data));
        }
        yield return null;
    }
    IEnumerator PrintNode(WzObject wzObject)
    {
        LinkedList<string> Parent = new LinkedList<string>();
        WzObject a = wzObject;
        string log2 = "";
        while (a is WzObjectChild)
        {
            a = (a as WzObjectChild).GetParent();
            Parent.AddFirst(a.GetName());
        }
        foreach (var iter in Parent)
        {
            log2 += iter + "/";
        }

        print(log2 + wzObject.GetName() +  "오브젝트 파싱 시작");
        string log = "";
        foreach (var child in wzObject.GetPropertiesDictionary())
        {
            if(child.Value.GetType() == MapleDataType.FLOAT)
            {

            log += child.Key + " = " + (float)child.Value.GetValue() + "\n";

            }
            else if (child.Value.GetType() == MapleDataType.INT)
            {

                log += child.Key + " = " + (int)child.Value.GetValue() + "\n";

            }
            else if (child.Value.GetType() == MapleDataType.STRING)
            {

                log += child.Key + " = " + (string)child.Value.GetValue() + "\n";

            }
            else if (child.Value.GetType() == MapleDataType.VECTOR)
            {
                log += child.Key + " = " + ((Vector2)child.Value.GetValue()).x.ToString() + " , " +((Vector2)child.Value.GetValue()).y.ToString() + "\n";
            }
        }
        if(log.Length!= 0)
        print(log);
        foreach (var child2 in wzObject.GetChildrenDictionary())
        {
            StartCoroutine(PrintNode(child2.Value));
        }
        yield return null;
    }
}
