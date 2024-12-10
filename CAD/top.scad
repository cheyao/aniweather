include <common.scad>

module PCB_Hole() {
	cube([PCB_WIDTH, PCB_HEIGHT, PCB_DEPTH], true);
}

module screw() {
	translate([0, 0, -PCB_DEPTH / 2 + WALL_THICKNESS - 0.0001])

	difference() {
		cylinder(h=SUPPORT_DEPTH, d=7);
		cylinder(h=SUPPORT_DEPTH+2, d=3);
	}
}

module case() {
	difference() {
		cube([CASE_WIDTH, CASE_HEIGHT, CASE_FRONT_DEPTH], true);

		translate([0, 0, WALL_THICKNESS + 0.0001]) PCB_Hole();

		// Wemos
		translate([CASE_WIDTH / 2, 5 - USB_WIDTH/2, USB_DEPTH/2])
		cube([30, USB_WIDTH, USB_DEPTH], true);

		// Battery
		translate([-CASE_WIDTH / 2, 10 + USB_WIDTH/2, USB_DEPTH/2])
		cube([30, USB_WIDTH, USB_DEPTH], true);
	}

	// Saber!
	mirror([1,0,0])
	resize(newsize=[CASE_WIDTH, CASE_HEIGHT, 0])
	translate([0, 0, -CASE_FRONT_DEPTH/2 - 1- 0.0001])
	linear_extrude(height=2, center=true, convexity = 15)
	import(file="saber.svg", center=true);
}

translate([(PCB_WIDTH - 4) / 2 - SCREW_OFFSET, (PCB_HEIGHT - 4) / 2 - SCREW_OFFSET, 0]) screw();
translate([(PCB_WIDTH - 4) / 2 - SCREW_OFFSET, -(PCB_HEIGHT - 4) / 2 + SCREW_OFFSET, 0]) screw();
translate([-(PCB_WIDTH - 4) / 2 + SCREW_OFFSET, (PCB_HEIGHT - 4) / 2 - SCREW_OFFSET, 0]) screw();
translate([-(PCB_WIDTH - 4) / 2 + SCREW_OFFSET, -(PCB_HEIGHT - 4) / 2 + SCREW_OFFSET, 0]) screw();

case();

