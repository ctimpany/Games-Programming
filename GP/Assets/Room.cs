using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Room : MonoBehaviour {

	BoxCollider2D bx2d;

	public int indexX, indexY;

	void Start() {
		bx2d = this.gameObject.AddComponent<BoxCollider2D> ();
		bx2d.isTrigger = true;
		bx2d.size = new Vector2 (LevelManager.roomWidth - PlayerController.instance.GetComponent<CircleCollider2D>().bounds.size.x * 1.1f, LevelManager.roomHeight - PlayerController.instance.GetComponent<CircleCollider2D>().bounds.size.y *1.1f);

		transform.position = (Vector3)(LevelManager.bottomLeft + new Vector2 ((indexX + 0.5f) * LevelManager.roomWidth, (indexY + 0.5f) * LevelManager.roomHeight)); 
	}

	public void SetIndex(int _x, int _y) {
		indexX = _x;
		indexY = _y;
	}

	void OnTriggerEnter2D(Collider2D col) {
		Camera.main.transform.position = new Vector3 (this.transform.position.x, this.transform.position.y, -10f);
	}

	/*void OnTriggerExit2D(Collider2D col) {
		Debug.Log ("Collision");
		Vector3 pos = Camera.main.transform.position;
		if (col.transform.position.x + col.bounds.max.x >= this.transform.position.x + (bx2d.size.x * 0.5f) && LevelManager.roomsArray[indexX+1, indexY] != null) {
			pos = new Vector3(LevelManager.roomsArray[indexX+1, indexY].transform.position.x, LevelManager.roomsArray[indexX+1, indexY].transform.position.y , -10f);
		} else if (col.transform.position.y + col.bounds.max.y >= this.transform.position.y + (bx2d.size.y * 0.5f) && LevelManager.roomsArray[indexX, indexY+1] != null) {
			pos = new Vector3(LevelManager.roomsArray[indexX, indexY+1].transform.position.x, LevelManager.roomsArray[indexX, indexY+1].transform.position.y , -10f);
		} else if (col.transform.position.x - col.bounds.min.x <= this.transform.position.x - (bx2d.size.x * 0.5f) && LevelManager.roomsArray[indexX-1, indexY] != null) {
			pos = new Vector3(LevelManager.roomsArray[indexX-1, indexY].transform.position.x, LevelManager.roomsArray[indexX-1, indexY].transform.position.y , -10f);
		} else if (col.transform.position.y - col.bounds.min.y <= this.transform.position.y - (bx2d.size.y * 0.5f) && LevelManager.roomsArray[indexX, indexY-1] != null) {
			pos = new Vector3(LevelManager.roomsArray[indexX, indexY-1].transform.position.x, LevelManager.roomsArray[indexX, indexY-1].transform.position.y , -10f);
		}

		Debug.Log (pos.ToString ());
		Camera.main.transform.position = pos;
	}*/
}
