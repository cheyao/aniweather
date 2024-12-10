include <common.scad>

module screw() {
	translate([0, 0, -PCB_DEPTH / 2 + WALL_THICKNESS - 0.0001])

	cylinder(h=SUPPORT_DEPTH+99999, d=3);
}

module main() {
	cube([CASE_WIDTH, CASE_HEIGHT, WALL_THICKNESS], true);
}

difference() {
	main();

	translate([(PCB_WIDTH - 4) / 2 - SCREW_OFFSET, (PCB_HEIGHT - 4) / 2 - SCREW_OFFSET, 0]) screw();
	translate([(PCB_WIDTH - 4) / 2 - SCREW_OFFSET, -(PCB_HEIGHT - 4) / 2 + SCREW_OFFSET, 0]) screw();
	translate([-(PCB_WIDTH - 4) / 2 + SCREW_OFFSET, (PCB_HEIGHT - 4) / 2 - SCREW_OFFSET, 0]) screw();
	translate([-(PCB_WIDTH - 4) / 2 + SCREW_OFFSET, -(PCB_HEIGHT - 4) / 2 + SCREW_OFFSET, 0]) screw();

	cube([LCD_WIDTH, LCD_HEIGHT, 500], true);
}
