import VPlay 2.0
import QtQuick 2.0

GameWindow {
  id: gameWindow

  // you get free licenseKeys as a V-Play customer or in your V-Play Trial
  // with a licenseKey, you get the best development experience:
  //  * No watermark shown
  //  * No license reminder every couple of minutes
  //  * No fading V-Play logo
  // you can generate one from http://v-play.net/license/trial, then enter it below:
  licenseKey: "C308D5AD3E216DD82C413339613F59D311CD7818B644AC06B27E45C1CA86019DF487637178E3A61D75C2C998588DE22CB02590A355E77FE168AD1A170BF59774A846A00AE7A9E65F516B1B78A0BB0DF12BF8D666E0D24AC3C1699BBE844C2E615F4227D37E18A2555A9B4CE646B17F01431B2E4170889E1EA99CD6ACF956D7BBF3B7C874CA19C376E58762ED6B39AE49F77BF572415216060CC8D321D2A24E339410E462707CDBEFA0A0E62D21C3E62CEE9CB18223D227C5231C2524D1FE8B5642D1D49ED3B088B92CB0747283DC55FF683050125F988E4DB64AC69AA4F24D41087A21C0F983D178272D12F5E009C8EC6332B8BEB7F20E19A4AAD9BCF4FC2AA291C00882056EB8A807CDCE63D48FB81FFB8955D88E5F833416FF6AE1F63DDA2E17BD0970ED9FD04717641A66E0EEBD30"

  activeScene: scene

  // the size of the Window can be changed at runtime by pressing Ctrl (or Cmd on Mac) + the number keys 1-8
  // the content of the logical scene size (480x320 for landscape mode by default) gets scaled to the window size based on the scaleMode
  // you can set this size to any resolution you would like your project to start with, most of the times the one of your main target device
  width: 320
  height: 480

  EntityManager {
    id: entityManager
  }

  Scene {
    id: scene

    property string gameState: "wait"
    property int score: 0

    function startGame() {
        scene.gameState = "play";
    }

    function stopGame() {
        scene.gameState = "gameOver";
    }

    function reset() {
        scene.gameState = "wait";
        score = 0;
        pipe1.x = 400;
        pipe1.y = 30+Math.random()*200;
        pipe2.x = 640;
        pipe2.y = 30+Math.random()*200;
        player.x = 160;
        player.y = 180;
    }

    // the "logical size" - the scene content is auto-scaled to match the GameWindow size
    width: 320
    height: 480

    sceneAlignmentY: "bottom"


    PhysicsWorld {
        debugDrawVisible: false
        gravity.y: scene.gameState == "wait" ? 27 : 0
    }

    Image {
        id: bg
        source: "../assets/bg.png"

        anchors.horizontalCenter: scene.horizontalCenter
        anchors.bottom: scene.gameWindowAnchorItem.bottom
    }

    Pipe {
        id: pipe1
        x: 400
        y: 30+Math.random()*200
    }

    Pipe {
        id: pipe2
        x: 640
        y: 30+Math.random()*200
    }

    Ground {
        anchors.horizontalCenter: scene.horizontalCenter
        anchors.bottom: scene.gameWindowAnchorItem.bottom
    }

    Player {
        id: player
        x: 160; y: 180
    }

    Text {
        text: scene.score
        color: "white"
        anchors.horizontalCenter: scene.horizontalCenter
        y: 30
        font.pixelSize: 30
    }

    MouseArea {
        anchors.fill: scene.gameWindowAnchorItem
        onPressed: {
            if (scene.gameState == "wait") {
                scene.startGame();
                player.push();
            } else if (scene.gameState == "play") {
                player.push();
            } else if (scene.gameState == "gameOver") {
                scene.reset();
            }
        }
    }
  }
}

