import VPlayApps 1.0
import QtQuick 2.0

App {
    // You get free licenseKeys from http://v-play.net/licenseKey
    // With a licenseKey you can:
    //  * Publish your games & apps for the app stores
    //  * Remove the V-Play Splash Screen or set a custom one (available with the Pro Licenses)
    //  * Add plugins to monetize, analyze & improve your apps (available with the Pro Licenses)
    licenseKey: "91C94DBE5185F012761E8AF45137CB51E617DAB27EA6DF12EE2D08D208006EBBBA8CDAA027E48FDF227F3A701FA9A9DD0F03F58D34DC69E9EACC8600D0689ECC8CB10BE03FD2553B77FA00782DDF2C044196AD9E933EBB270BB70A6311AD9208C9730F8E551EF5DB24385BF59A0ADB8AABB458EC8866CF991991DA692A84FF55F58771E04F5997946998E33064F1AE59E89B08D980799B7CC0916D1F722AA6DDC7EFDD7C94E6345B1B78CF2A7C4F9141DF74C12EE6A8A6758FEBC81C16B5D09B6BDD13ABC4EF4D8F1F197D17536EE030BB412DEA4E0905041781CAE9A97A2E504B138601F0671A91B4369458A2246848F35683C5ED362EF0CC3EC2E5F3B8E191D5E7270A5EB954EEE4C198985AEFBCD24A920246CFC68B35C1447EFCC01CC4FF"

    FontLoader {
        id: materialFont
        source: "../assets/MaterialIcons-Regular.ttf"
    }

    onInitTheme: {
        Theme.iconFont = materialFont;
        Theme.navigationBar.backgroundColor = "#2d3c50";
        Theme.navigationBar.titleColor = "#ffffff";
        Theme.navigationBar.dividerColor = "#00ffffff";
        Theme.navigationBar.height = dp(100);
    }

    Navigation {
        id: navigation
        navDrawerButton: IconButtonBarItem {
            icon: "\ue5d2"
            onClicked: navigation.drawer.toggle()
        }
        navigationMode: navigationModeDrawer

        NavigationItem {
            title: qsTr("Planner")
            icon: "\ue5c3"

            NavigationStack {
                id: stack
                ListPage {
                    title: qsTr("Agendy")
                    model: 100
                    delegate: SimpleRow {
                        text: "foo"
                        onSelected: stack.push(page2)
                    }

                    rightBarItem: NavigationBarRow {
                        IconButtonBarItem {
                            icon: "\ue87c"
                        }
                    }
                    Component {
                        id: page2
                        Page {
                            title: qsTr("Wooo")
                            leftBarItem: IconButtonBarItem {
                                icon: "\ue5ca"
                            }
                        }
                    }
                }
            }
        }
        NavigationItem {
            title: qsTr("Settings")
        }
        NavigationItem {
            title: qsTr("Reports")
        }
        NavigationItem {
            title: qsTr("Logout")
        }
    }
}
