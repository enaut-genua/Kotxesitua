# Exekutagarri baten iturburu kodea definitu
target_sources(
	${PROJECT_NAME}		# Kode artxiboak gehitu nahi dizkiogun exekutagarriaren izena (hau da, Kotxesitua).
		PRIVATE				# Aukera hauek proiektu honentzat bakarrik izatea
			main.c				# Kodea
			includes.h			# Kodea
			input.h				# Kodea
			input.c				# Kodea
			kotxea.h			# Kodea
			kotxea.c			# Kodea
			dijkstra.h			# Kodea
			dijkstra.c 			# Kodea
)

# Konpilazio gurutzatua aktibatuta badago
if(KONP_GURUTZ)
	# Exekutagarri baten iturburu kodea definitu
	target_sources(
		${PROJECT_NAME}	# Kode artxiboak gehitu nahi dizkiogun exekutagarriaren izena (hau da, Kotxesitua).
			PRIVATE			# Aukera hauek proiektu honentzat bakarrik izatea
				hardware.h		# Kodea
				hardware.c		# Kodea
	)
endif()


# Beste artxibo bat gehitu nahiko bagenio, idatzi artxibo horren izena eta yasta.
# Kontuan eduki artxibo hauek denak artxibo hau dagoen karpeta berean egon behar dutela.