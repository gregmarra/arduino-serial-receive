# arduino-serial-receive

This Arduino program receives a comma separated series of numbers from serial, and places them into an array.

For example, sending "1,2,3,4\n" will update the array serialInputParams to contain [1,2,3,4]

A few particular elements of this:
* **serialEvent** – This default Arduino function receives and buffers a serial message.
* **strtok** – Using this function to split the input
* **atoi** – Converting character reprentations of numbers ("123") into ints (123)

I found it difficult to get going with this, so I hope putting this up as an example will make this easier for others.
