#!/bin/bash
# Sprawdzenie, czy podano nazwę programu jako argument
if [ -z "$1" ]; then
  echo "Użycie: $0 nazwa_programu"
  exit 1
fi
# Uruchomienie programu jako procesu potomnego
./$1 &
# Pobranie PID procesu potomnego
child_pid=$!
# Wyświetlanie informacji o procesie rodzica i potomnym co sekundę
while true; do
  echo "Proces rodzica: $$"
  echo "Proces potomny: $child_pid"
  echo ""
  sleep 1
done
