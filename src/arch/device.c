#include <stddef.h>
#include <stdint.h>

#include <arch/device.h>
#include <lib/string.h>
#include <mm/heap.h>

device_t * headDevice = 0;

device_t * device_add (const char * name) {
	device_t * dev = (device_t *)heap_alloc (sizeof (device_t));
	strcpy (name, dev->name);
	
	if (headDevice == 0) {
		headDevice = dev;
	} else {
		device_t * temp = headDevice;
		while (temp->next != 0) {
			temp = temp->next;
		}
		temp->next = dev;
	}
	dev->next = 0;
	return dev;
}

size_t device_read (device_t * dev, void * ptr, size_t bytes, uint64_t offset) {
	return dev->read (dev, ptr, bytes, offset);
}

size_t device_write (device_t * dev, void * ptr, size_t bytes, uint64_t offset) {
	return dev->write (dev, ptr, bytes, offset);
}

size_t device_ioctl (device_t * dev, int one, int two, int three) {
	return dev->ioctl (dev, one, two, three);
}