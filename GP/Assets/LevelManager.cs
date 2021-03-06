﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LevelManager : MonoBehaviour {

	public int numRoomsX, numRoomsY;
	public string seed;
	public bool useRandomSeed;
	public static Room[,] roomsArray;
	public static float roomWidth, roomHeight;
	public static Vector2 bottomLeft;

	int maxRooms, minRooms, roomsCount;
	GameObject roomParent;
	Room startRoom, endRoom;

	System.Random pseudoRandom;

	// Use this for initialization
	void Start () {
		roomsArray = new Room[numRoomsX, numRoomsY];
		maxRooms = Mathf.RoundToInt((roomsArray.GetLength (0) * roomsArray.GetLength (1)) * 0.4f);
		minRooms = Mathf.RoundToInt((roomsArray.GetLength (0) * roomsArray.GetLength (1)) * 0.1f);
		roomsCount = 0;
		roomWidth = (Camera.main.ScreenToWorldPoint (new Vector2 (Camera.main.pixelWidth, 0f)) - Camera.main.ScreenToWorldPoint (new Vector2 (0f, 0f))).x;
		roomHeight = (Camera.main.ScreenToWorldPoint (new Vector2 (0f, Camera.main.pixelHeight)) - Camera.main.ScreenToWorldPoint (new Vector2 (0f, 0f))).y;
		//Debug.Log (roomWidth.ToString());
		//Debug.Log (roomHeight.ToString ());

		if (useRandomSeed) {
			seed = System.DateTime.Now.ToString ();
		}

		pseudoRandom = new System.Random(seed.GetHashCode());

		roomParent = new GameObject ("Rooms");

		while (roomsCount < minRooms) {
			Debug.Log ("Generating");
			roomsCount = 0;
			ClearRoomsArray ();
			RoomGeneration ();
		}
		GenerateLoops ();
		GenerateWalls ();
		GenerateEndRoom ();
		GenerateEnemies ();
	}
	
	// Update is called once per frame
	void Update () {
		
	}


	void ClearRoomsArray(){
		for (int x = 0; x < roomsArray.GetLength (0); x++) {
			for (int y = 0; y < roomsArray.GetLength (1); y++) {
				Room r = roomsArray [x, y];
				if (r != null) {
					roomsArray [x, y] = null;
					Destroy (r.gameObject);
				}
			}
		}
	}


	Queue<Room> openSet = new Queue<Room> ();
	Room currentRoom;

	void RoomGeneration() {

		bottomLeft = Vector2.zero - Vector2.right * (roomWidth * roomsArray.GetLength (0)) / 2f - Vector2.up * (roomHeight * roomsArray.GetLength (1)) / 2f;

		if (numRoomsX % 2 == 0) {
			bottomLeft.x += roomWidth / 2;
		}
		if (numRoomsY % 2 == 0) {
			bottomLeft.y += roomHeight / 2;
		}

		//Debug.Log (bottomLeft.ToString ());

		GenerateStartRoom ((roomsArray.GetLength(0)-1)/2, (roomsArray.GetLength(1)-1)/2);

		while (openSet.Count > 0 && roomsCount < maxRooms) {
			currentRoom = openSet.Dequeue ();

			float chance = 50f;

			if(pseudoRandom.Next(0, 100) < chance && currentRoom.indexX+1 < roomsArray.GetLength(0) && roomsArray[currentRoom.indexX +1, currentRoom.indexY] == null) {
				GenerateRoom (currentRoom.indexX+1, currentRoom.indexY);
				//chance /= 2;
			}

			if(pseudoRandom.Next(0, 100) < chance && currentRoom.indexX-1 > -1 && roomsArray[currentRoom.indexX-1, currentRoom.indexY] == null) {
				GenerateRoom (currentRoom.indexX-1, currentRoom.indexY);
				//chance /= 2;
			}

			if(pseudoRandom.Next(0, 100) < chance && currentRoom.indexY+1 < roomsArray.GetLength(1)&& roomsArray[currentRoom.indexX, currentRoom.indexY+1] == null) {
				GenerateRoom (currentRoom.indexX, currentRoom.indexY+1);
				//chance /= 2;
			}

			if(pseudoRandom.Next(0, 100) < chance && currentRoom.indexY-1 > -1&& roomsArray[currentRoom.indexX, currentRoom.indexY-1] == null) {
				GenerateRoom (currentRoom.indexX, currentRoom.indexY-1);
				//chance /= 2;
			}
		}
	}

	void GenerateRoom(int _x, int _y) {
		GameObject room = new GameObject ("room");
		roomsArray[_x,_y] = room.AddComponent<Room> ();
		roomsArray[_x,_y].SetIndex (_x, _y);
		room.transform.parent = roomParent.transform;

		GameObject g = new GameObject ("Floor");
		g.transform.parent = room.transform;
		SpriteRenderer sr = g.AddComponent<SpriteRenderer> ();
		Sprite sp = sr.sprite = Sprite.Create (new Texture2D (32,32), new Rect(Vector2.zero, new Vector2( roomWidth, roomHeight)), Vector2.one * 0.5f);
		sr.color = new Color (0.5f, 0.5f, 0.5f);
		//Random.ColorHSV (0f, 1f, 1f, 1f, 0.3f, 0.6f);
		g.transform.localScale = new Vector3 (100f, 100f);
		//sp.bounds.size = new Vector2 (LevelManager.roomWidth, LevelManager.roomHeight);

		openSet.Enqueue(roomsArray[_x,_y]);
		roomsCount++;
	}

	void GenerateStartRoom(int _x, int _y) {
		GameObject room = new GameObject ("room");
		startRoom = roomsArray[_x,_y] = room.AddComponent<Room> ();
		roomsArray[_x,_y].SetIndex (_x, _y);
		room.transform.parent = roomParent.transform;

		GameObject g = new GameObject ("Floor");
		g.transform.parent = room.transform;
		SpriteRenderer sr = g.AddComponent<SpriteRenderer> ();
		Sprite sp = sr.sprite = Sprite.Create (new Texture2D (32,32), new Rect(Vector2.zero, new Vector2( roomWidth, roomHeight)), Vector2.one * 0.5f);
		sr.color = Color.green;
		//Random.ColorHSV (0f, 1f, 1f, 1f, 0.3f, 0.6f);
		g.transform.localScale = new Vector3 (100f, 100f);
		//sp.bounds.size = new Vector2 (LevelManager.roomWidth, LevelManager.roomHeight);

		openSet.Enqueue(roomsArray[_x,_y]);
		roomsCount++;
	}

	void GenerateEndRoom(){
		for (int x = 0; x < roomsArray.GetLength (0); x++) {
			for (int y = 0; y < roomsArray.GetLength (1); y++) {
				int adjacentRooms = 0;
				Room r = roomsArray [x, y];
				if (r != null) {
					if (r.indexX + 1 < roomsArray.GetLength (0) && roomsArray [r.indexX + 1, r.indexY] != null) {
						adjacentRooms++;
					}
					if (r.indexY + 1 < roomsArray.GetLength (1) && roomsArray [r.indexX, r.indexY + 1] != null) {
						adjacentRooms++;
					}
					if (r.indexX - 1 >= 0 && roomsArray [r.indexX - 1, r.indexY] != null) {
						adjacentRooms++;
					}
					if (r.indexY - 1 >= 0 && roomsArray [r.indexX, r.indexY - 1] != null) {
						adjacentRooms++;
					}

					if (adjacentRooms == 1) {
						float dis = Mathf.Abs (new Vector2((float)(r.indexX - startRoom.indexX), (float)(r.indexY - startRoom.indexY)).magnitude);
						float chance = 1f - (1f / dis);

						if (pseudoRandom.Next(0, 100)/100f < chance) {
							r.transform.FindChild ("Floor").GetComponent<SpriteRenderer> ().color = Color.red;
							//Debug.Log ("hello");
							return;
						}
					}
				}
			}
		}
	}

	void GenerateWalls(){
		for (int x = 0; x < roomsArray.GetLength (0); x++) {
			for (int y = 0; y < roomsArray.GetLength (1); y++) {
				Room r = roomsArray [x, y];
				if (r != null) {
					if (r.indexX + 1 > roomsArray.GetLength (0) - 1 || roomsArray [r.indexX + 1, r.indexY] == null) {
						createWall (r, new Vector3 ((roomWidth * 0.5f) - 0.25f, 0), new Vector2 (0.5f, roomHeight));
					}

					if (r.indexX - 1 < 0 || roomsArray [r.indexX - 1, r.indexY] == null) {
						createWall (r, new Vector3 ((roomWidth * -0.5f) + 0.25f, 0), new Vector2 (0.5f, roomHeight)); 
					}

					if (r.indexY + 1 > roomsArray.GetLength (1) - 1 || roomsArray [r.indexX, r.indexY + 1] == null) {
						createWall (r, new Vector3 (0, (roomHeight * 0.5f) - 0.25f), new Vector2 (roomWidth, 0.5f));
					}

					if (r.indexY - 1 < 0 || roomsArray [r.indexX, r.indexY - 1] == null) {
						createWall (r, new Vector3 (0, (roomHeight * -0.5f) + 0.25f), new Vector2 (roomWidth, 0.5f));
					}
				}
			}
		}
	}

	void createWall(Room r, Vector3 position, Vector2 size){
		BoxCollider2D col = r.gameObject.AddComponent<BoxCollider2D> ();
		col.offset = position;
		col.size = size;

		GameObject g = new GameObject ("Wall");
		g.transform.parent = r.transform;
		SpriteRenderer sr = g.AddComponent<SpriteRenderer> ();
		Sprite sp = sr.sprite = Sprite.Create (new Texture2D (32,32), new Rect(Vector2.zero, size), Vector2.one * 0.5f);
		sr.color = new Color (0f, 0f, 0f, 1f);
		g.transform.localScale = new Vector3 (100f, 100f);
		g.transform.localPosition = position;
		sr.sortingOrder = 1;
	}

	void GenerateLoops(){
		for (int x = 0; x < roomsArray.GetLength (0); x++) {
			for (int y = 0; y < roomsArray.GetLength (1); y++) {
				int adjacentRooms = 0, adjacentDiagonalRooms = 0;
				Room r = roomsArray [x, y];
				if (r != null && (x != (roomsArray.GetLength(0)-1)/2 || y != (roomsArray.GetLength(1)-1)/2)) {
					if (r.indexX + 1 < roomsArray.GetLength (0) && roomsArray [r.indexX + 1, r.indexY] != null) {
						adjacentRooms++;
					}
					if (r.indexX + 1 < roomsArray.GetLength (0) && r.indexY + 1 < roomsArray.GetLength (1)  && roomsArray [r.indexX + 1, r.indexY + 1] != null) {
						adjacentDiagonalRooms++;
					}
					if (r.indexY + 1 < roomsArray.GetLength (1) && roomsArray [r.indexX, r.indexY + 1] != null) {
						adjacentRooms++;
					}
					if (r.indexX - 1 >= 0 && r.indexY + 1 < roomsArray.GetLength (1)  && roomsArray [r.indexX - 1, r.indexY + 1] != null) {
						adjacentDiagonalRooms++;
					}
					if (r.indexX - 1 >= 0 && roomsArray [r.indexX - 1, r.indexY] != null) {
						adjacentRooms++;
					}
					if (r.indexX - 1 >= 0 && r.indexY - 1 >= 0  && roomsArray [r.indexX - 1, r.indexY - 1] != null) {
						adjacentDiagonalRooms++;
					}
					if (r.indexY - 1 >= 0 && roomsArray [r.indexX, r.indexY - 1] != null) {
						adjacentRooms++;
					}
					if (r.indexX + 1 < roomsArray.GetLength (0) && r.indexY - 1 >= 0  && roomsArray [r.indexX + 1, r.indexY - 1] != null) {
						adjacentDiagonalRooms++;
					}
				}

				if((adjacentRooms+adjacentDiagonalRooms) >= 7){
					if (adjacentDiagonalRooms >= adjacentRooms) {
						roomsArray [x, y] = null;
						roomsCount--;
						Destroy (r.gameObject);
					}
				}
			}
		}
	}


	void GenerateEnemies(){
		for (int x = 0; x < roomsArray.GetLength (0); x++) {
			for (int y = 0; y < roomsArray.GetLength (1); y++) {
				Room r = roomsArray [x, y];
				if (r != null && (x != (roomsArray.GetLength(0)-1)/2 || y != (roomsArray.GetLength(1)-1)/2)) {
					int numEnemies = pseudoRandom.Next (0, 3);

					switch (numEnemies) {
					case 2:
						Vector3 position = r.gameObject.transform.position;
						position.y += (roomHeight / 5);
						GameObject enemy1 = (GameObject)Instantiate (
							                    Resources.Load ("Enemy"),
							                    position,
							                    new Quaternion ());
						enemy1.transform.parent = r.gameObject.transform;

						position = r.gameObject.transform.position;
						position.y -= (roomHeight / 5);
						GameObject enemy2 = (GameObject)Instantiate (
							                    Resources.Load ("Enemy"),
							                    position,
							                    new Quaternion ());
						enemy2.transform.parent = r.gameObject.transform;

						break;
					case 1:
						GameObject enemy = (GameObject)Instantiate (
							Resources.Load ("Enemy"),
							r.gameObject.transform.position,
							new Quaternion ());
						enemy.transform.parent = r.gameObject.transform;

						break;
					}
				}
			}
		}
	}
}
