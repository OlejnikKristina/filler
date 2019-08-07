$(document).ready(function()
{
	var		map;
	var		start_pos;
	var		map_x;
	var		map_y;
	var		score_player_o;
	var		score_player_x;

	score_player_o = 0;
	score_player_x = 0;
	$("#button").click(function(){
		map = $('#map_src').val();
	});

	function init_map_size()
	{
		var		size_pos;
		var		result;
	
		size_pos = map.indexOf("Plateau ");
		map_y = map.charAt(size_pos + "Plateau ".length);
		map_y += map.charAt(size_pos + "Plateau ".length + 1);
	
		map_y = map.charAt(size_pos + "Plateau ".length);
		map_y += map.charAt(size_pos + "Plateau ".length + 1);
	
		map_x = map.charAt(size_pos + "Plateau ".length + 3);
		map_x += map.charAt(size_pos + "Plateau ".length + 4);

		result = map_x + map_y;
		$("#paragraph").append(" X " + map_x + " Y " + map_y + "result: " + result + "<br>");
	}

	function set_speed()
	{
		var		speed;
	
		speed = $("input[name=choose_speed]:checked", "#map_src_form").val();
		if (String(speed) == "speed_slow")
			return (900);
		if (String(speed) == "speed_fast")
			return (100);
		if (String(speed) == "speed_super_fast")
			return (30);
		return (300);
	}

	function creat_grid_from_div()
	{
		var		i;
	
		i = 0;
		while (i < map_x * map_y)
		{
			$("#grid").append("<div class='spot_div'></div>")
			i++;
		}
	}

	function add_move_player_x(x, y)
	{
		var		spot;
		var		spot_pos;
	
		//core_player_x += 1;
		spot = "#grid div:nth-child(";
		if (0 < y)
		{
			spot_pos = x + (y * map_x);
			$(spot + spot_pos + ')').addClass("player_x");
		}
		else
			$(spot + x + ')').addClass("player_x");
	}

	function add_move_player_o(x, y, character)
	{
		var		spot_pos;
		var		spot;
		var		class_name;

		spot = "#grid div:nth-child(";
		class_name = "player_o";
		if (0 < y)
		{
			spot_pos = x + (y * map_x);
			$(spot + spot_pos  + ')').addClass(class_name);
		}
		else
			$(spot + x + ')').addClass(class_name);
	}

	function add_move(map_arr)
	{
		var		x;
		var		y;
	
		x = 0;
		y = 0;
		while (y < map_y)
		{
			while (x < map_x)
			{
				if (map_arr[y][x] == "O")
					add_move_player_o(x, y, map_arr[y][x]);
				if (map_arr[y][x] == "X")
					add_move_player_x(x, y);
				x++;
			}
			x = 0;
			y++;
		}
	}

	function move_start_pos()
	{
		start_pos = map.indexOf("000", Number(start_pos));
	}

	function add_score()
	{
		var		got_player_o;
		var		got_player_x;
	
		got_player_o = map.indexOf("got (O)", Number(start_pos));
		got_player_x = map.indexOf("got (X)", Number(start_pos));
		if (got_player_o == -1 && got_player_x == -1)
			return (false);
		if (Number(got_player_o) < Number(got_player_x) && (Number(got_player_o) != -1))
		{
			score_player_o++;
			$(".score_player_o").text("Scores player O: " + score_player_o);
		}
		else
		{
			score_player_x++;
			$(".score_player_x").text("Scores player X: " + score_player_x);
		}
		got_player_o = 0;
		got_player_x = 0;
	}

	function fill_one_map_piece(map_arr)
	{
		var		start;
		var		i;

		i = 0;
		start = Number(start_pos) + 3;
		while (i < Number(map_y))
		{
			map_arr[i] = map.substring(start, Number(start) + Number(map_x) + 1);
			start += Number(map_x) + 5;
			i++;
		}
		add_score();
		start_pos = start;
	}

	$("#button").click(function()
	{
		var		map_arr = [];
		var		speed;
		var		i;

		i = 0;
		init_map_size();
		creat_grid_from_div();
		speed = set_speed();
		start_pos = map.indexOf("000");
		while (i < 500)
		{
			setTimeout(fill_one_map_piece, Number(speed) * i, map_arr);
			setTimeout(add_move, Number(speed) * i, map_arr);
			setTimeout(move_start_pos, Number(speed) * i);
		//	$("p").append("Minus found" + start_pos + " RUN_GAME: " + RUN_GAME+ "<br>");
			i++;
		}
	});
});
