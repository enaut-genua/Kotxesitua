# Raspberry Pi-ren konpilazio gurutzatua egiteko.

# Raspberry Pi-ren sistema nolakoa izango den esan.
set(CMAKE_SYSTEM_NAME Linux)	# Sistema Eragilea
set(CMAKE_SYSTEM_PROCESSOR arm)	# Prozesagailuaren arkitektura

# Herraminten izenak zeintzuk diren esan. Hauek berez automatikoki detektatzen ditu normal konpilatzen bada.
set(CMAKE_AR			"arm-linux-gnueabihf-ar")			# Programa
set(CMAKE_ASM_COMPILER	"arm-linux-gnueabihf-as")			# Programa
set(CMAKE_C_COMPILER	"arm-linux-gnueabihf-gcc")			# Programa
set(CMAKE_LINKER		"arm-linux-gnueabihf-ld")			# Programa
set(CMAKE_OBJCOPY		"arm-linux-gnueabihf-objcopy")		# Programa
set(CMAKE_RANLIB		"arm-linux-gnueabihf-gcc-ranlib")	# Programa
set(CMAKE_SIZE			"arm-linux-gnueabihf-size")			# Programa
set(CMAKE_STRIP			"arm-linux-gnueabihf-strip")		# Programa
