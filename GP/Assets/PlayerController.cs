using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour {

	public static PlayerController instance;
	public float playerSpeed;
	Rigidbody2D rb2d;

	private GameObject healthSprite;

	public float maxPlayerHealth;
	public float playerHealth;

	void Awake() {
		Time.timeScale = 1.0f;
		rb2d = this.GetComponent<Rigidbody2D> ();
		playerHealth = maxPlayerHealth;
		healthSprite = transform.FindChild ("PlayerHealth").gameObject;
		instance = this;
	}

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void FixedUpdate () {
		Vector3 pos = Camera.main.WorldToScreenPoint(transform.position);
		Vector3 dir = Input.mousePosition - pos;
		float angle = Mathf.Atan2(dir.y, dir.x) * Mathf.Rad2Deg;
		transform.rotation = Quaternion.AngleAxis(angle, Vector3.forward);

		float y = Input.GetAxis ("Vertical");
		float x = Input.GetAxis ("Horizontal");

		rb2d.velocity = new Vector2 (x, y).normalized * playerSpeed * Time.deltaTime;

		if (playerHealth <= 0) {
			playerHealth = 0;
			UILoader loader = GetComponent<UILoader> ();
			loader.loadUI ("Game Over");
			Time.timeScale = 0.0f;
		}

		healthSprite.transform.localScale = new Vector2 ((playerHealth / maxPlayerHealth) * 0.9f, (playerHealth / maxPlayerHealth) * 0.9f);

		if (Input.GetKeyDown(KeyCode.Space))
		{
			Fire();
		}
	}

	void Fire()
	{

		Vector3 pos = Camera.main.WorldToScreenPoint(transform.position);
		Vector3 dir = Input.mousePosition - pos;
		// Create the Bullet from the Bullet Prefab
		GameObject bullet = (GameObject)Instantiate (
			             Resources.Load ("Bullet"),
			             transform.FindChild ("BulletSpawn").position,
			             transform.rotation);

		// Add velocity to the bullet
		bullet.GetComponent<Rigidbody2D>().velocity = dir.normalized * 10;

		// Destroy the bullet after 2 seconds
		Destroy(bullet, 1.0f);        
	}

	void OnCollisionStay2D(Collision2D collisionInfo) {
		foreach (ContactPoint2D contact in collisionInfo.contacts) {
			if (contact.collider.gameObject.tag == "Enemy") {
				Debug.Log ("collision with Enemy");
				playerHealth -= 1;
			}
			else
				Debug.Log ("Other collision: Player");
		}
	}
}
