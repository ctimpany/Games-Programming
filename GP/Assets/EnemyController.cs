using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyController : MonoBehaviour {

	public static EnemyController instance;
	public float enemySpeed;
	Rigidbody2D rb2d;

	private GameObject healthSprite;

	public float maxEnemyHealth;
	public float enemyHealth;
	public bool move;
	public bool playerInRoom;

	void Awake() {
		move = false;
		enemyHealth = maxEnemyHealth;
		rb2d = this.GetComponent<Rigidbody2D> ();
		healthSprite = transform.FindChild ("EnemyHealth").gameObject;
		instance = this;
	}

	// Use this for initialization
	void Start () {

	}

	// Update is called once per frame
	void FixedUpdate () {
		if (enemyHealth < 0)
			enemyHealth = 0;

		healthSprite.transform.localScale = new Vector2 ((enemyHealth / maxEnemyHealth) * 0.9f, (enemyHealth / maxEnemyHealth) * 0.9f);

		if(move)
			transform.position = Vector2.MoveTowards (transform.position, PlayerController.instance.transform.position, enemySpeed * Time.deltaTime);
		if (enemyHealth <= 0)
			Destroy (gameObject);
	}

	void OnCollisionEnter2D(Collision2D collisionInfo) {
		foreach (ContactPoint2D contact in collisionInfo.contacts) {
			if (contact.collider.gameObject.tag == "Bullet") {
				Debug.Log ("collision with Bullet");
				Destroy (contact.collider.gameObject);
				enemyHealth -= 10;
			} else if (contact.collider.gameObject.tag == "Player") {
				move = false;
			}else
				Debug.Log ("Other collision: Enemy");
		}
	}

	void OnCollisionExit2D(Collision2D collisionInfo) {
		if (!move && playerInRoom)
			move = true;
	}

}
