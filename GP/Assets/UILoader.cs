using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UILoader : MonoBehaviour {
	private GameObject canvas;
	// Use this for initialization
	void Start () {
		canvas = GameObject.Find ("Canvas");
	}
	
	// Update is called once per frame
	void Update () {
		
	}

	public void loadUI(string name){
		GameObject uiPrefab = Resources.Load ("UI/" + name) as GameObject;
		GameObject ui = Instantiate (uiPrefab);
		ui.transform.SetParent (canvas.transform, false);
		//GUI.FocusControl (name);
	}

	public GameObject loadUIReturn(string name){
		GameObject uiPrefab = Resources.Load ("UI/" + name) as GameObject;
		GameObject ui = Instantiate (uiPrefab);
		ui.transform.SetParent (canvas.transform, false);
		//GUI.FocusControl (name);
		return ui;
	}

	public void destroyUI(GameObject obj){
		Destroy (obj.gameObject);
	}
}
