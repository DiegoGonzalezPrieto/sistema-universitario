# Sistema de Gestión de una Carrera universitaria

## Desarrolladores

- José Arias
- Franco Formía
- Diego G. Prieto
- Lucho Santostefano

## Librerías de Terceros

- RLUTIL
	- Licencia WTFPL


------

# Ramas

* MAIN - versiones v1 v2 v3

* DEVELOP - desarrollo

* RAMAS-POR-FUNCIONALIDAD

-----------------------------

## Crear rama nueva

* git switch develop

* git switch -c clase-archivo

-----------------------------

## Flujo de trabajo diario

* // hago mi trabajo sobre cpp / h

* git add (los archivos que quiero modificar)

* git commit -m ("mensaje de lo que hice")

* // opcional, voy pusheado a mi rama remota
	* git push -u origin (nombre de mi rama)

-----------------------------

## Traerme nuevos cambios de DEVELOP (opcional)

* git switch develop
* git pull
* git switch clase-archivo
* git merge develop 

-----------------------------

## Cuando termino mi funcionalidad

* git push
* ! merge de la rama a develop usando Pull Request

