# Keychron q10 max ansi with encoder QMK Keymap

QMK custom firmware with 6 layers. Each layer has color indication.

#### Compiling:
- To compile it you can read docs here [https://docs.qmk.fm/newbs_building_firmware](https://docs.qmk.fm/newbs_building_firmware)
- Basic repo [https://github.com/Keychron/qmk_firmware](https://github.com/Keychron/qmk_firmware) - wireless_playground branch
- You should to remove the dip_switch_update_kb function from the keyboards\keychron\q10_max\q10_max.c because it is used in keymap.c

#### Features:
- To enable GAMING layer use Tap dance on ins button(double tap)
- To toggle rgb(without writing to noeeprom) use Tap dance on ins button(triple tap)
- There is also additional layer MAC_FN_1 for common usage