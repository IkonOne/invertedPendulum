If using linux, make sure to disable brltty (it interferes with the Serial port).

```
systemctl disable brltty-udev.service
systemctl mask brltty-udev.service # to disable on boot
```