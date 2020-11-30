#include "jvm/jvm.h"

int main() 
{

	// Create a wrapper for the net.minecraft.client.Minecraft
	auto mc_class = g_jvm->find_class("bao");

	// Creats a wrapper for the singleton instance of net.minecraft.client.Minecraft
	// by calling the static object method getMinecraft
	auto mc_inst = mc_class->call_static_object("B", "bao", nullptr);

	// Creats a wrapper for the player object by getting the field thePlayer
	auto player_inst = mc_inst->get_object("h", "blk");

	// Gets the players current yaw by getting the field rotationYaw from the parent class Entity
	auto yaw = player_inst->get_float("y");

	if (yaw != 0)
	{
		// Set the players yaw to 0
		player_inst->set_float("y", 0);
	}


}