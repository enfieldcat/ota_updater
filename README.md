ota_updater
===========

Code for ESP32 Over The Air (OTA) updates using any http/https web server as source.

Provides a check that the updated image is matches the sha256 checksum of the source
before changeing the boot partition. The metadata for the image to be updated is
held in a separate metadata file, eg<pre>
name: esp32.img
size: 869584
sequence: 1586743799
sha256: ee4d000f93b754e61d2c400517735e8a45719de863fefbfcabd182f62cb473ca
</pre>

Note the main logic to be replicated between projects is in the ota_contrl tab / file.

For a more detailed description see <a href="https://conferre.cf/arduino/ota_updater.php">https://conferre.cf/arduino/ota_updater.php</a>

