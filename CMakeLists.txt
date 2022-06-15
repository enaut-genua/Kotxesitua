# Behartu CMake bertsioa 3.16.0 baino handiago izaten
cmake_minimum_required(VERSION 3.16.0)

#add_subdirectory(mapa_sortzailea)

# Konpilazio gurutzatua aktibatu edo desaktibatzen duen interruptorea (ON/OFF). Automatikoki itzalita (OFF).
option(KONP_GURUTZ "Konpilazio gurutzatua Raspberry Pi-rako" OFF)

# Konfiguratu konpilazio gurutzatua.
if(KONP_GURUTZ)
	set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/raspberrypi.cmake")		# Raspberry Pi-rako konpilatzaileak non dauden definitzen duen artxiboa non dauden esan CMake programari.
	message(STATUS "Raspberry Pi-rako konpilazio gurutzatua konfiguratuta.")	# Printf(mezua)
endif()
	
# Proiektua definitu
project(
	Kotxesitua		# Proiektuaren izenburua
		LANGUAGES 		# Proiektuan erabiliko den hizkuntza
			C
		DESCRIPTION		# Deskripzioa
			"Kotxe robota kontrolatzen duen programa"
)

# Exekutagarri berri bat gehitu, proiektuaren izen berarekin.
add_executable(${PROJECT_NAME})

# Gehitu kodearen karpeta
add_subdirectory("src/")

# Exekutagarri baten propietateak ezarri
set_target_properties(
	${PROJECT_NAME}		# Propietateak ezarri nahi dizkiogun exekutagarriaren izena (hau da, kasu honetan Kotxesitua).
		PROPERTIES			# Propietateak
			C_STANDARD 11			# C-ren estandarra C11-ra jarri. (Ez da inportantea, bertsio hau jarri dut jartzeagatik zeozer.)
			C_STANDARD_REQUIRED ON	# Lehen aukeratu den C estandarra beharrezkoa izatea.
			C_EXTENSIONS OFF		# Konpilatzailearen aukerazko C-ren extensioak desgaitu.
)

# Exekutagarri baten konpilazio aukerak
target_compile_options(
	${PROJECT_NAME}					# Konpilazio aukerak ezarri nahi dizkiogun exekutagarriaren izena (hau da, Kotxesitua).
		PRIVATE							# Aukera hauek proiektu honentzat bakarrik izatea
			$<$<C_COMPILER_ID:GNU>:			# Konpilatzailea GCC (G.C.C: GNU Compiler Colection, horregatik GNU) bada:
				-Wall							# Abisu guztiak aktibatu
				-Wextra							# Abisu extrak aktibatu
				# -Werror							# Abisu guztiak errore bilakatu
				-pedantic						# C-lengoaiari buruzko (sintaxia) abisuak aktibatu
				-pedantic-errors				# Aurreko abisuak errore bilakatu.
			>
)

# Konpilazio gurutzatua aktibatuta badago:
if(KONP_GURUTZ)

	# Gehitu dependentzien karpeta
	add_subdirectory("dep/")

	# Exekutagarri baten konpilazio aukerak
	target_compile_options(
		${PROJECT_NAME}				# Konpilazio aukerak ezarri nahi dizkiogun exekutagarriaren izena (hau da, Kotxesitua).
			PRIVATE						# Aukera hauek proiektu honentzat bakarrik izatea
				$<$<C_COMPILER_ID:GNU>:		# Konpilatzailea GCC (G.C.C: GNU Compiler Colection, horregatik GNU) bada:
					-DRASPBERRY					# '#define RASPBERRY' egiteko esan konpilatzaileari.
				>
	)

	# Exekutagarri baten liburutegiak definitu.
	target_link_libraries(
		${PROJECT_NAME}				# Liburutegiak gehitu nahi dizkiogun exekutagarriaren izena (hau da, Kotxesitua).
			PRIVATE						# Aukera hauek proiektu honentzat bakarrik izatea
				wiringPi					# Aukeratu wiringPi liburutegia eta erabili gure proiektuan.
	)
endif()

