# Wiring Pi-ko *.h eta *.so guztiak liburutegi bat bezala definituko dugu.

# Gehitu liburutegi bat.
add_library(wiringPi SHARED IMPORTED GLOBAL)

# Liburutegi baten propietateak ezarri
set_target_properties(
	wiringPi						# Propietateak ezarri nahi dizkiogun liburutegiaren izena (hau da, kasu honetan wiringPi).
		PROPERTIES						# Propietateak
			IMPORTED_LOCATION 				# *.so-ak non dauden esan.
				"${CMAKE_CURRENT_SOURCE_DIR}/lib/libwiringPi.so"
			INTERFACE_INCLUDE_DIRECTORIES	# Inkluituko diren *.h-ak non dauden esan.
				"${CMAKE_CURRENT_SOURCE_DIR}/includes"
)