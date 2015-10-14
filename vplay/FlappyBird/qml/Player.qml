import VPlay 2.0
import QtQuick 2.0

EntityBase {
    id: player
    entityType: "player"

    CircleCollider {
        id: collider

        radius: 13
        anchors.centerIn: parent
    }

    SpriteSequenceVPlay {
        id: bird
        anchors.centerIn: parent

        rotation: collider.linearVelocity.y / 10

        running: scene.gameState != "gameOver"

        SpriteVPlay {
            frameCount: 3
            frameRate: 10
            frameWidth: 34
            frameHeight: 24
            source: "../assets/bird.png"
        }
    }

    function push() {
        collider.body.linearVelocity = Qt.point(0, 0);
        var localForwardVelocity = collider.body.toWorldVector(Qt.point(0, -280));
        collider.body.applyLinearImpulse(localForwardVelocity, collider.body.getWorldCenter());
    }
}

