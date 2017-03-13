using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour {

	public static PlayerController instance;
	public float playerSpeed;
	Rigidbody2D rb2d;

	void Awake() {
		rb2d = this.GetComponent<Rigidbody2D> ();
		instance = this;
	}

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void FixedUpdate () {
		float y = Input.GetAxis ("Vertical");
		float x = Input.GetAxis ("Horizontal");

		rb2d.velocity = new Vector2 (x, y).normalized * playerSpeed * Time.deltaTime;
	}
}
