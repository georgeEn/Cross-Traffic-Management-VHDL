library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
entity Traffic is
	Port (  FirstBit, SecondBit: in std_logic_vector(1 downto 0)
		Direction:           in std_logic_vector(3 downto 0)
		slot:                in boolean          -- True is free, False is busy
	);
	-- N is "00"
	-- W is "01"
	-- S is "10"
	-- E is "11"
end Traffic;

architecture behavior of Traffic is 
	-- Declaration of type and signal
	type t_state is (NW, EN, SE, WS);
	signal state: t_state;
	signal FirstBit: Direction(3) and Direction(2);
	signal SecondBit: Direction(1) and Direction(0);
begin
	process (Direction) is
		if (Direction /= "0000" & Direction /= "1111")
		then
			case State is
				when NW =>
					if (secondBit /= "01" & slot = true)
					then State <= WS 
					else State <= NW 
					end if;
				when WS =>
					if (secondBit /= "10" & slot = true)
					then State <= SE 
					else State <= WS 
					end if;
				when SE =>
					if (secondBit /= "11" & slot = true)
					then State <= EN 
					else State <= SE 
					end if;
				when EN =>
					if (secondBit /= "00" & slot = true)
					then State <= MW 
					else State <= EN 
					end if;
			end case;
		end if;
	end process;
end behavior;
