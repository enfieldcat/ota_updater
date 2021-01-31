ota_updater
===========

Code for ESP32 Over The Air (OTA) updates using any http/https web server as source. Thus the generated binary could have been compied using the arduino-cli, and does not depend on the Arduino IDE running.

Provides a check that the updated image is matches the sha256 checksum of the source
before changeing the boot partition. The metadata for the image to be updated is
held in a separate metadata file, eg<pre>
name: esp32.img
size: 869584
sequence: 1586743799
sha256: ee4d000f93b754e61d2c400517735e8a45719de863fefbfcabd182f62cb473ca
</pre>

Note the main logic to be replicated between projects is in the ota_contrl tab / file. ota_updater is a wrapper to call this.

On a PHP enabled server you can use code to generate metadata file based on the most recent deployment of the binary image.
Here is an example of such PHP code:
<pre>
&lt;?php
$filename="esp32.img";
$statvar=stat($filename);
$sha256var=hash_file("sha256", $filename);
echo "name: $filename\n";
echo "size: $statvar[size]\n";
echo "sequence: $statvar[mtime]\n";
echo "sha256: $sha256var\n"; ?&gt;
</pre>

The result this generates is a simple 4 line yaml file as shown eariler above.

For a more detailed description see <a href="https://conferre.cf/arduino/ota_updater.php">https://conferre.cf/arduino/ota_updater.php</a>

