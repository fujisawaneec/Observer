#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>

/// <summary>
/// コライダー Observer
/// </summary>
class Collider {
public:
	/// <summary>
	/// 当たったら呼ばれる関数
	/// </summary>
	virtual void OnCollision() {};
};

/// <summary>
/// 衝突マネージャ Subject
/// </summary>
class CollisionManager {
private:
	std::vector<Collider*> colliders_;

public:

	/// <summary>
	/// コライダーを追加する
	/// </summary>
	/// <param name="collider">コライダー</param>
	void AddCollider(Collider* collider) {
		// 重複追加を避ける
		if (std::find(colliders_.begin(), colliders_.end(), collider) != colliders_.end()) {
			return;
		}
		// 追加
		colliders_.push_back(collider);
	}

	/// <summary>
	/// 全ての当たり判定
	/// </summary>
	void TestAllCollisions() {

		// 総当たり
		auto itA = colliders_.begin();
		for (; itA != colliders_.end(); itA++) {
			auto itB = itA + 1;
			for (; itB != colliders_.end(); itB++) {
				// サンプルなので、必ず当たることにする

				(*itA)->OnCollision();
				(*itB)->OnCollision();
			}
		}
	}

	/// <summary>
	/// オブザーバーに衝突を通知する
	/// </summary>
	void NotifyCollision() {
		for (auto& collider : colliders_) {
			collider->OnCollision();
		}
	}
};

/// <summary>
/// 自キャラ
/// </summary>
class Player final : public Collider {
public:
	/// <summary>
	/// 当たったら呼ばれる関数
	/// </summary>
	void OnCollision() {
		printf("Player: OnCollision\n");
	};
};

/// <summary>
/// 敵キャラ
/// </summary>
class Enemy final : public Collider {
public:
	/// <summary>
	/// 当たったら呼ばれる関数
	/// </summary>
	void OnCollision() {
		printf("Enemy: OnCollision\n");
	};
};

int main()
{
	Player player;
	Enemy enemy;
	CollisionManager collisionManager;

	collisionManager.AddCollider(&player);
	collisionManager.AddCollider(&enemy);

	collisionManager.TestAllCollisions();

	system("pause");

	return 0;
}