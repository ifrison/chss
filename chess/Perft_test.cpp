#include "Perft.h"

#include "fen/Fen.h"
#include "representation/State.h"

#include <gtest/gtest.h>

TEST(Perft, A) {
	constexpr auto state = chss::fen::Parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	constexpr auto nodesVisited = std::array<std::int64_t, 7>{20, 400, 8902, 197281, 4865609, 119060324, 3195901860};
	for (int depth = 0; depth < 4; ++depth) {
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth + 1), nodesVisited[depth]);
	}
}

TEST(Perft, B) {
	constexpr auto state = chss::fen::Parse("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
	constexpr auto nodesVisited = std::array<std::int64_t, 6>{48, 2039, 97862, 4085603, 193690690, 8031647685};
	for (int depth = 0; depth < 3; ++depth) {
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth + 1), nodesVisited[depth]);
	}
}

TEST(Perft, C) {
	constexpr auto state = chss::fen::Parse("n1n5/PPPk4/8/8/8/8/4Kppp/5N1N b - - 0 1");
	constexpr auto nodesVisited = std::array<std::int64_t, 6>{24, 496, 9483, 182838, 3605103, 71179139};
	for (int depth = 0; depth < 4; ++depth) {
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth + 1), nodesVisited[depth]);
	}
}

TEST(Perft, DISABLED_X) {
	constexpr auto state = chss::fen::Parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	EXPECT_EQ(chss::MoveGeneration::Perft(state, 6), 119060324);
}

TEST(Perft, DISABLED_Y) {
	constexpr auto state = chss::fen::Parse("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
	EXPECT_EQ(chss::MoveGeneration::Perft(state, 5), 193690690);
}

TEST(Perft, DISABLED_Z) {
	EXPECT_EQ(chss::MoveGeneration::Perft(chss::fen::Parse("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1"), 7), 178633661);
	EXPECT_EQ(
		chss::MoveGeneration::Perft(
			chss::fen::Parse("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1"),
			6),
		706045033);
	EXPECT_EQ(chss::MoveGeneration::Perft(chss::fen::Parse("1k6/1b6/8/8/7R/8/8/4K2R b K - 0 1"), 5), 1063513);
	EXPECT_EQ(chss::MoveGeneration::Perft(chss::fen::Parse("3k4/3p4/8/K1P4r/8/8/8/8 b - - 0 1"), 6), 1134888);
	EXPECT_EQ(chss::MoveGeneration::Perft(chss::fen::Parse("8/8/4k3/8/2p5/8/B2P2K1/8 w - - 0 1"), 6), 1015133);
	EXPECT_EQ(chss::MoveGeneration::Perft(chss::fen::Parse("8/8/1k6/2b5/2pP4/8/5K2/8 b - d3 0 1"), 6), 1440467);
	EXPECT_EQ(chss::MoveGeneration::Perft(chss::fen::Parse("5k2/8/8/8/8/8/8/4K2R w K - 0 1"), 6), 661072);
	EXPECT_EQ(chss::MoveGeneration::Perft(chss::fen::Parse("3k4/8/8/8/8/8/8/R3K3 w Q - 0 1"), 6), 803711);
	EXPECT_EQ(chss::MoveGeneration::Perft(chss::fen::Parse("r3k2r/1b4bq/8/8/8/8/7B/R3K2R w KQkq - 0 1"), 4), 1274206);
	EXPECT_EQ(chss::MoveGeneration::Perft(chss::fen::Parse("r3k2r/8/3Q4/8/8/5q2/8/R3K2R b KQkq - 0 1"), 4), 1720476);
	EXPECT_EQ(chss::MoveGeneration::Perft(chss::fen::Parse("2K2r2/4P3/8/8/8/8/8/3k4 w - - 0 1"), 6), 3821001);
	EXPECT_EQ(chss::MoveGeneration::Perft(chss::fen::Parse("8/8/1P2K3/8/2n5/1q6/8/5k2 b - - 0 1"), 5), 1004658);
	EXPECT_EQ(chss::MoveGeneration::Perft(chss::fen::Parse("4k3/1P6/8/8/8/8/K7/8 w - - 0 1"), 6), 217342);
	EXPECT_EQ(chss::MoveGeneration::Perft(chss::fen::Parse("8/P1k5/K7/8/8/8/8/8 w - - 0 1"), 6), 92683);
	EXPECT_EQ(chss::MoveGeneration::Perft(chss::fen::Parse("K1k5/8/P7/8/8/8/8/8 w - - 0 1"), 6), 2217);
	EXPECT_EQ(chss::MoveGeneration::Perft(chss::fen::Parse("8/k1P5/8/1K6/8/8/8/8 w - - 0 1"), 7), 567584);
	EXPECT_EQ(chss::MoveGeneration::Perft(chss::fen::Parse("8/8/2k5/5q2/5n2/8/5K2/8 b - - 0 1"), 4), 23527);
}

TEST(Perft, Test001) {
	constexpr auto state = chss::fen::Parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 20),
		std::pair<int, std::int64_t>(2, 400),
		std::pair<int, std::int64_t>(3, 8902),
		std::pair<int, std::int64_t>(4, 197281),
		std::pair<int, std::int64_t>(5, 4865609),
		std::pair<int, std::int64_t>(6, 119060324)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test002) {
	constexpr auto state = chss::fen::Parse("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 48),
		std::pair<int, std::int64_t>(2, 2039),
		std::pair<int, std::int64_t>(3, 97862),
		std::pair<int, std::int64_t>(4, 4085603),
		std::pair<int, std::int64_t>(5, 193690690)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test003) {
	constexpr auto state = chss::fen::Parse("4k3/8/8/8/8/8/8/4K2R w K - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 15),
		std::pair<int, std::int64_t>(2, 66),
		std::pair<int, std::int64_t>(3, 1197),
		std::pair<int, std::int64_t>(4, 7059),
		std::pair<int, std::int64_t>(5, 133987),
		std::pair<int, std::int64_t>(6, 764643)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test004) {
	constexpr auto state = chss::fen::Parse("4k3/8/8/8/8/8/8/R3K3 w Q - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 16),
		std::pair<int, std::int64_t>(2, 71),
		std::pair<int, std::int64_t>(3, 1287),
		std::pair<int, std::int64_t>(4, 7626),
		std::pair<int, std::int64_t>(5, 145232),
		std::pair<int, std::int64_t>(6, 846648)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test005) {
	constexpr auto state = chss::fen::Parse("4k2r/8/8/8/8/8/8/4K3 w k - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 5),
		std::pair<int, std::int64_t>(2, 75),
		std::pair<int, std::int64_t>(3, 459),
		std::pair<int, std::int64_t>(4, 8290),
		std::pair<int, std::int64_t>(5, 47635),
		std::pair<int, std::int64_t>(6, 899442)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test006) {
	constexpr auto state = chss::fen::Parse("r3k3/8/8/8/8/8/8/4K3 w q - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 5),
		std::pair<int, std::int64_t>(2, 80),
		std::pair<int, std::int64_t>(3, 493),
		std::pair<int, std::int64_t>(4, 8897),
		std::pair<int, std::int64_t>(5, 52710),
		std::pair<int, std::int64_t>(6, 1001523)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test007) {
	constexpr auto state = chss::fen::Parse("4k3/8/8/8/8/8/8/R3K2R w KQ - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 26),
		std::pair<int, std::int64_t>(2, 112),
		std::pair<int, std::int64_t>(3, 3189),
		std::pair<int, std::int64_t>(4, 17945),
		std::pair<int, std::int64_t>(5, 532933),
		std::pair<int, std::int64_t>(6, 2788982)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test008) {
	constexpr auto state = chss::fen::Parse("r3k2r/8/8/8/8/8/8/4K3 w kq - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 5),
		std::pair<int, std::int64_t>(2, 130),
		std::pair<int, std::int64_t>(3, 782),
		std::pair<int, std::int64_t>(4, 22180),
		std::pair<int, std::int64_t>(5, 118882),
		std::pair<int, std::int64_t>(6, 3517770)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test009) {
	constexpr auto state = chss::fen::Parse("8/8/8/8/8/8/6k1/4K2R w K - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 12),
		std::pair<int, std::int64_t>(2, 38),
		std::pair<int, std::int64_t>(3, 564),
		std::pair<int, std::int64_t>(4, 2219),
		std::pair<int, std::int64_t>(5, 37735),
		std::pair<int, std::int64_t>(6, 185867)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test010) {
	constexpr auto state = chss::fen::Parse("8/8/8/8/8/8/1k6/R3K3 w Q - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 15),
		std::pair<int, std::int64_t>(2, 65),
		std::pair<int, std::int64_t>(3, 1018),
		std::pair<int, std::int64_t>(4, 4573),
		std::pair<int, std::int64_t>(5, 80619),
		std::pair<int, std::int64_t>(6, 413018)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test011) {
	constexpr auto state = chss::fen::Parse("4k2r/6K1/8/8/8/8/8/8 w k - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 3),
		std::pair<int, std::int64_t>(2, 32),
		std::pair<int, std::int64_t>(3, 134),
		std::pair<int, std::int64_t>(4, 2073),
		std::pair<int, std::int64_t>(5, 10485),
		std::pair<int, std::int64_t>(6, 179869)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test012) {
	constexpr auto state = chss::fen::Parse("r3k3/1K6/8/8/8/8/8/8 w q - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 4),
		std::pair<int, std::int64_t>(2, 49),
		std::pair<int, std::int64_t>(3, 243),
		std::pair<int, std::int64_t>(4, 3991),
		std::pair<int, std::int64_t>(5, 20780),
		std::pair<int, std::int64_t>(6, 367724)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test013) {
	constexpr auto state = chss::fen::Parse("r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 26),
		std::pair<int, std::int64_t>(2, 568),
		std::pair<int, std::int64_t>(3, 13744),
		std::pair<int, std::int64_t>(4, 314346),
		std::pair<int, std::int64_t>(5, 7594526),
		std::pair<int, std::int64_t>(6, 179862938)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test014) {
	constexpr auto state = chss::fen::Parse("r3k2r/8/8/8/8/8/8/1R2K2R w Kkq - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 25),
		std::pair<int, std::int64_t>(2, 567),
		std::pair<int, std::int64_t>(3, 14095),
		std::pair<int, std::int64_t>(4, 328965),
		std::pair<int, std::int64_t>(5, 8153719),
		std::pair<int, std::int64_t>(6, 195629489)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test015) {
	constexpr auto state = chss::fen::Parse("r3k2r/8/8/8/8/8/8/2R1K2R w Kkq - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 25),
		std::pair<int, std::int64_t>(2, 548),
		std::pair<int, std::int64_t>(3, 13502),
		std::pair<int, std::int64_t>(4, 312835),
		std::pair<int, std::int64_t>(5, 7736373),
		std::pair<int, std::int64_t>(6, 184411439)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test016) {
	constexpr auto state = chss::fen::Parse("r3k2r/8/8/8/8/8/8/R3K1R1 w Qkq - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 25),
		std::pair<int, std::int64_t>(2, 547),
		std::pair<int, std::int64_t>(3, 13579),
		std::pair<int, std::int64_t>(4, 316214),
		std::pair<int, std::int64_t>(5, 7878456),
		std::pair<int, std::int64_t>(6, 189224276)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test017) {
	constexpr auto state = chss::fen::Parse("1r2k2r/8/8/8/8/8/8/R3K2R w KQk - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 26),
		std::pair<int, std::int64_t>(2, 583),
		std::pair<int, std::int64_t>(3, 14252),
		std::pair<int, std::int64_t>(4, 334705),
		std::pair<int, std::int64_t>(5, 8198901),
		std::pair<int, std::int64_t>(6, 198328929)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test018) {
	constexpr auto state = chss::fen::Parse("2r1k2r/8/8/8/8/8/8/R3K2R w KQk - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 25),
		std::pair<int, std::int64_t>(2, 560),
		std::pair<int, std::int64_t>(3, 13592),
		std::pair<int, std::int64_t>(4, 317324),
		std::pair<int, std::int64_t>(5, 7710115),
		std::pair<int, std::int64_t>(6, 185959088)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test019) {
	constexpr auto state = chss::fen::Parse("r3k1r1/8/8/8/8/8/8/R3K2R w KQq - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 25),
		std::pair<int, std::int64_t>(2, 560),
		std::pair<int, std::int64_t>(3, 13607),
		std::pair<int, std::int64_t>(4, 320792),
		std::pair<int, std::int64_t>(5, 7848606),
		std::pair<int, std::int64_t>(6, 190755813)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test020) {
	constexpr auto state = chss::fen::Parse("4k3/8/8/8/8/8/8/4K2R b K - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 5),
		std::pair<int, std::int64_t>(2, 75),
		std::pair<int, std::int64_t>(3, 459),
		std::pair<int, std::int64_t>(4, 8290),
		std::pair<int, std::int64_t>(5, 47635),
		std::pair<int, std::int64_t>(6, 899442)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test021) {
	constexpr auto state = chss::fen::Parse("4k3/8/8/8/8/8/8/R3K3 b Q - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 5),
		std::pair<int, std::int64_t>(2, 80),
		std::pair<int, std::int64_t>(3, 493),
		std::pair<int, std::int64_t>(4, 8897),
		std::pair<int, std::int64_t>(5, 52710),
		std::pair<int, std::int64_t>(6, 1001523)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test022) {
	constexpr auto state = chss::fen::Parse("4k2r/8/8/8/8/8/8/4K3 b k - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 15),
		std::pair<int, std::int64_t>(2, 66),
		std::pair<int, std::int64_t>(3, 1197),
		std::pair<int, std::int64_t>(4, 7059),
		std::pair<int, std::int64_t>(5, 133987),
		std::pair<int, std::int64_t>(6, 764643)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test023) {
	constexpr auto state = chss::fen::Parse("r3k3/8/8/8/8/8/8/4K3 b q - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 16),
		std::pair<int, std::int64_t>(2, 71),
		std::pair<int, std::int64_t>(3, 1287),
		std::pair<int, std::int64_t>(4, 7626),
		std::pair<int, std::int64_t>(5, 145232),
		std::pair<int, std::int64_t>(6, 846648)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test024) {
	constexpr auto state = chss::fen::Parse("4k3/8/8/8/8/8/8/R3K2R b KQ - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 5),
		std::pair<int, std::int64_t>(2, 130),
		std::pair<int, std::int64_t>(3, 782),
		std::pair<int, std::int64_t>(4, 22180),
		std::pair<int, std::int64_t>(5, 118882),
		std::pair<int, std::int64_t>(6, 3517770)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test025) {
	constexpr auto state = chss::fen::Parse("r3k2r/8/8/8/8/8/8/4K3 b kq - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 26),
		std::pair<int, std::int64_t>(2, 112),
		std::pair<int, std::int64_t>(3, 3189),
		std::pair<int, std::int64_t>(4, 17945),
		std::pair<int, std::int64_t>(5, 532933),
		std::pair<int, std::int64_t>(6, 2788982)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test026) {
	constexpr auto state = chss::fen::Parse("8/8/8/8/8/8/6k1/4K2R b K - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 3),
		std::pair<int, std::int64_t>(2, 32),
		std::pair<int, std::int64_t>(3, 134),
		std::pair<int, std::int64_t>(4, 2073),
		std::pair<int, std::int64_t>(5, 10485),
		std::pair<int, std::int64_t>(6, 179869)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test027) {
	constexpr auto state = chss::fen::Parse("8/8/8/8/8/8/1k6/R3K3 b Q - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 4),
		std::pair<int, std::int64_t>(2, 49),
		std::pair<int, std::int64_t>(3, 243),
		std::pair<int, std::int64_t>(4, 3991),
		std::pair<int, std::int64_t>(5, 20780),
		std::pair<int, std::int64_t>(6, 367724)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test028) {
	constexpr auto state = chss::fen::Parse("4k2r/6K1/8/8/8/8/8/8 b k - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 12),
		std::pair<int, std::int64_t>(2, 38),
		std::pair<int, std::int64_t>(3, 564),
		std::pair<int, std::int64_t>(4, 2219),
		std::pair<int, std::int64_t>(5, 37735),
		std::pair<int, std::int64_t>(6, 185867)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test029) {
	constexpr auto state = chss::fen::Parse("r3k3/1K6/8/8/8/8/8/8 b q - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 15),
		std::pair<int, std::int64_t>(2, 65),
		std::pair<int, std::int64_t>(3, 1018),
		std::pair<int, std::int64_t>(4, 4573),
		std::pair<int, std::int64_t>(5, 80619),
		std::pair<int, std::int64_t>(6, 413018)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test030) {
	constexpr auto state = chss::fen::Parse("r3k2r/8/8/8/8/8/8/R3K2R b KQkq - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 26),
		std::pair<int, std::int64_t>(2, 568),
		std::pair<int, std::int64_t>(3, 13744),
		std::pair<int, std::int64_t>(4, 314346),
		std::pair<int, std::int64_t>(5, 7594526),
		std::pair<int, std::int64_t>(6, 179862938)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test031) {
	constexpr auto state = chss::fen::Parse("r3k2r/8/8/8/8/8/8/1R2K2R b Kkq - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 26),
		std::pair<int, std::int64_t>(2, 583),
		std::pair<int, std::int64_t>(3, 14252),
		std::pair<int, std::int64_t>(4, 334705),
		std::pair<int, std::int64_t>(5, 8198901),
		std::pair<int, std::int64_t>(6, 198328929)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test032) {
	constexpr auto state = chss::fen::Parse("r3k2r/8/8/8/8/8/8/2R1K2R b Kkq - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 25),
		std::pair<int, std::int64_t>(2, 560),
		std::pair<int, std::int64_t>(3, 13592),
		std::pair<int, std::int64_t>(4, 317324),
		std::pair<int, std::int64_t>(5, 7710115),
		std::pair<int, std::int64_t>(6, 185959088)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test033) {
	constexpr auto state = chss::fen::Parse("r3k2r/8/8/8/8/8/8/R3K1R1 b Qkq - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 25),
		std::pair<int, std::int64_t>(2, 560),
		std::pair<int, std::int64_t>(3, 13607),
		std::pair<int, std::int64_t>(4, 320792),
		std::pair<int, std::int64_t>(5, 7848606),
		std::pair<int, std::int64_t>(6, 190755813)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test034) {
	constexpr auto state = chss::fen::Parse("1r2k2r/8/8/8/8/8/8/R3K2R b KQk - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 25),
		std::pair<int, std::int64_t>(2, 567),
		std::pair<int, std::int64_t>(3, 14095),
		std::pair<int, std::int64_t>(4, 328965),
		std::pair<int, std::int64_t>(5, 8153719),
		std::pair<int, std::int64_t>(6, 195629489)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test035) {
	constexpr auto state = chss::fen::Parse("2r1k2r/8/8/8/8/8/8/R3K2R b KQk - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 25),
		std::pair<int, std::int64_t>(2, 548),
		std::pair<int, std::int64_t>(3, 13502),
		std::pair<int, std::int64_t>(4, 312835),
		std::pair<int, std::int64_t>(5, 7736373),
		std::pair<int, std::int64_t>(6, 184411439)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test036) {
	constexpr auto state = chss::fen::Parse("r3k1r1/8/8/8/8/8/8/R3K2R b KQq - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 25),
		std::pair<int, std::int64_t>(2, 547),
		std::pair<int, std::int64_t>(3, 13579),
		std::pair<int, std::int64_t>(4, 316214),
		std::pair<int, std::int64_t>(5, 7878456),
		std::pair<int, std::int64_t>(6, 189224276)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test037) {
	constexpr auto state = chss::fen::Parse("8/1n4N1/2k5/8/8/5K2/1N4n1/8 w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 14),
		std::pair<int, std::int64_t>(2, 195),
		std::pair<int, std::int64_t>(3, 2760),
		std::pair<int, std::int64_t>(4, 38675),
		std::pair<int, std::int64_t>(5, 570726),
		std::pair<int, std::int64_t>(6, 8107539)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test038) {
	constexpr auto state = chss::fen::Parse("8/1k6/8/5N2/8/4n3/8/2K5 w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 11),
		std::pair<int, std::int64_t>(2, 156),
		std::pair<int, std::int64_t>(3, 1636),
		std::pair<int, std::int64_t>(4, 20534),
		std::pair<int, std::int64_t>(5, 223507),
		std::pair<int, std::int64_t>(6, 2594412)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test039) {
	constexpr auto state = chss::fen::Parse("8/8/4k3/3Nn3/3nN3/4K3/8/8 w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 19),
		std::pair<int, std::int64_t>(2, 289),
		std::pair<int, std::int64_t>(3, 4442),
		std::pair<int, std::int64_t>(4, 73584),
		std::pair<int, std::int64_t>(5, 1198299),
		std::pair<int, std::int64_t>(6, 19870403)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test040) {
	constexpr auto state = chss::fen::Parse("K7/8/2n5/1n6/8/8/8/k6N w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 3),
		std::pair<int, std::int64_t>(2, 51),
		std::pair<int, std::int64_t>(3, 345),
		std::pair<int, std::int64_t>(4, 5301),
		std::pair<int, std::int64_t>(5, 38348),
		std::pair<int, std::int64_t>(6, 588695)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test041) {
	constexpr auto state = chss::fen::Parse("k7/8/2N5/1N6/8/8/8/K6n w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 17),
		std::pair<int, std::int64_t>(2, 54),
		std::pair<int, std::int64_t>(3, 835),
		std::pair<int, std::int64_t>(4, 5910),
		std::pair<int, std::int64_t>(5, 92250),
		std::pair<int, std::int64_t>(6, 688780)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test042) {
	constexpr auto state = chss::fen::Parse("8/1n4N1/2k5/8/8/5K2/1N4n1/8 b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 15),
		std::pair<int, std::int64_t>(2, 193),
		std::pair<int, std::int64_t>(3, 2816),
		std::pair<int, std::int64_t>(4, 40039),
		std::pair<int, std::int64_t>(5, 582642),
		std::pair<int, std::int64_t>(6, 8503277)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test043) {
	constexpr auto state = chss::fen::Parse("8/1k6/8/5N2/8/4n3/8/2K5 b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 16),
		std::pair<int, std::int64_t>(2, 180),
		std::pair<int, std::int64_t>(3, 2290),
		std::pair<int, std::int64_t>(4, 24640),
		std::pair<int, std::int64_t>(5, 288141),
		std::pair<int, std::int64_t>(6, 3147566)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test044) {
	constexpr auto state = chss::fen::Parse("8/8/3K4/3Nn3/3nN3/4k3/8/8 b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 4),
		std::pair<int, std::int64_t>(2, 68),
		std::pair<int, std::int64_t>(3, 1118),
		std::pair<int, std::int64_t>(4, 16199),
		std::pair<int, std::int64_t>(5, 281190),
		std::pair<int, std::int64_t>(6, 4405103)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test045) {
	constexpr auto state = chss::fen::Parse("K7/8/2n5/1n6/8/8/8/k6N b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 17),
		std::pair<int, std::int64_t>(2, 54),
		std::pair<int, std::int64_t>(3, 835),
		std::pair<int, std::int64_t>(4, 5910),
		std::pair<int, std::int64_t>(5, 92250),
		std::pair<int, std::int64_t>(6, 688780)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test046) {
	constexpr auto state = chss::fen::Parse("k7/8/2N5/1N6/8/8/8/K6n b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 3),
		std::pair<int, std::int64_t>(2, 51),
		std::pair<int, std::int64_t>(3, 345),
		std::pair<int, std::int64_t>(4, 5301),
		std::pair<int, std::int64_t>(5, 38348),
		std::pair<int, std::int64_t>(6, 588695)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test047) {
	constexpr auto state = chss::fen::Parse("B6b/8/8/8/2K5/4k3/8/b6B w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 17),
		std::pair<int, std::int64_t>(2, 278),
		std::pair<int, std::int64_t>(3, 4607),
		std::pair<int, std::int64_t>(4, 76778),
		std::pair<int, std::int64_t>(5, 1320507),
		std::pair<int, std::int64_t>(6, 22823890)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test048) {
	constexpr auto state = chss::fen::Parse("8/8/1B6/7b/7k/8/2B1b3/7K w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 21),
		std::pair<int, std::int64_t>(2, 316),
		std::pair<int, std::int64_t>(3, 5744),
		std::pair<int, std::int64_t>(4, 93338),
		std::pair<int, std::int64_t>(5, 1713368),
		std::pair<int, std::int64_t>(6, 28861171)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test049) {
	constexpr auto state = chss::fen::Parse("k7/B7/1B6/1B6/8/8/8/K6b w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 21),
		std::pair<int, std::int64_t>(2, 144),
		std::pair<int, std::int64_t>(3, 3242),
		std::pair<int, std::int64_t>(4, 32955),
		std::pair<int, std::int64_t>(5, 787524),
		std::pair<int, std::int64_t>(6, 7881673)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test050) {
	constexpr auto state = chss::fen::Parse("K7/b7/1b6/1b6/8/8/8/k6B w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 7),
		std::pair<int, std::int64_t>(2, 143),
		std::pair<int, std::int64_t>(3, 1416),
		std::pair<int, std::int64_t>(4, 31787),
		std::pair<int, std::int64_t>(5, 310862),
		std::pair<int, std::int64_t>(6, 7382896)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test051) {
	constexpr auto state = chss::fen::Parse("B6b/8/8/8/2K5/5k2/8/b6B b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 6),
		std::pair<int, std::int64_t>(2, 106),
		std::pair<int, std::int64_t>(3, 1829),
		std::pair<int, std::int64_t>(4, 31151),
		std::pair<int, std::int64_t>(5, 530585),
		std::pair<int, std::int64_t>(6, 9250746)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test052) {
	constexpr auto state = chss::fen::Parse("8/8/1B6/7b/7k/8/2B1b3/7K b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 17),
		std::pair<int, std::int64_t>(2, 309),
		std::pair<int, std::int64_t>(3, 5133),
		std::pair<int, std::int64_t>(4, 93603),
		std::pair<int, std::int64_t>(5, 1591064),
		std::pair<int, std::int64_t>(6, 29027891)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test053) {
	constexpr auto state = chss::fen::Parse("k7/B7/1B6/1B6/8/8/8/K6b b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 7),
		std::pair<int, std::int64_t>(2, 143),
		std::pair<int, std::int64_t>(3, 1416),
		std::pair<int, std::int64_t>(4, 31787),
		std::pair<int, std::int64_t>(5, 310862),
		std::pair<int, std::int64_t>(6, 7382896)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test054) {
	constexpr auto state = chss::fen::Parse("K7/b7/1b6/1b6/8/8/8/k6B b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 21),
		std::pair<int, std::int64_t>(2, 144),
		std::pair<int, std::int64_t>(3, 3242),
		std::pair<int, std::int64_t>(4, 32955),
		std::pair<int, std::int64_t>(5, 787524),
		std::pair<int, std::int64_t>(6, 7881673)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test055) {
	constexpr auto state = chss::fen::Parse("7k/RR6/8/8/8/8/rr6/7K w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 19),
		std::pair<int, std::int64_t>(2, 275),
		std::pair<int, std::int64_t>(3, 5300),
		std::pair<int, std::int64_t>(4, 104342),
		std::pair<int, std::int64_t>(5, 2161211),
		std::pair<int, std::int64_t>(6, 44956585)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test056) {
	constexpr auto state = chss::fen::Parse("R6r/8/8/2K5/5k2/8/8/r6R w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 36),
		std::pair<int, std::int64_t>(2, 1027),
		std::pair<int, std::int64_t>(3, 29215),
		std::pair<int, std::int64_t>(4, 771461),
		std::pair<int, std::int64_t>(5, 20506480),
		std::pair<int, std::int64_t>(6, 525169084)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test057) {
	constexpr auto state = chss::fen::Parse("7k/RR6/8/8/8/8/rr6/7K b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 19),
		std::pair<int, std::int64_t>(2, 275),
		std::pair<int, std::int64_t>(3, 5300),
		std::pair<int, std::int64_t>(4, 104342),
		std::pair<int, std::int64_t>(5, 2161211),
		std::pair<int, std::int64_t>(6, 44956585)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test058) {
	constexpr auto state = chss::fen::Parse("R6r/8/8/2K5/5k2/8/8/r6R b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 36),
		std::pair<int, std::int64_t>(2, 1027),
		std::pair<int, std::int64_t>(3, 29227),
		std::pair<int, std::int64_t>(4, 771368),
		std::pair<int, std::int64_t>(5, 20521342),
		std::pair<int, std::int64_t>(6, 524966748)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test059) {
	constexpr auto state = chss::fen::Parse("6kq/8/8/8/8/8/8/7K w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 2),
		std::pair<int, std::int64_t>(2, 36),
		std::pair<int, std::int64_t>(3, 143),
		std::pair<int, std::int64_t>(4, 3637),
		std::pair<int, std::int64_t>(5, 14893),
		std::pair<int, std::int64_t>(6, 391507)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test060) {
	constexpr auto state = chss::fen::Parse("6KQ/8/8/8/8/8/8/7k b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 2),
		std::pair<int, std::int64_t>(2, 36),
		std::pair<int, std::int64_t>(3, 143),
		std::pair<int, std::int64_t>(4, 3637),
		std::pair<int, std::int64_t>(5, 14893),
		std::pair<int, std::int64_t>(6, 391507)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test061) {
	constexpr auto state = chss::fen::Parse("K7/8/8/3Q4/4q3/8/8/7k w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 6),
		std::pair<int, std::int64_t>(2, 35),
		std::pair<int, std::int64_t>(3, 495),
		std::pair<int, std::int64_t>(4, 8349),
		std::pair<int, std::int64_t>(5, 166741),
		std::pair<int, std::int64_t>(6, 3370175)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test062) {
	constexpr auto state = chss::fen::Parse("6qk/8/8/8/8/8/8/7K b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 22),
		std::pair<int, std::int64_t>(2, 43),
		std::pair<int, std::int64_t>(3, 1015),
		std::pair<int, std::int64_t>(4, 4167),
		std::pair<int, std::int64_t>(5, 105749),
		std::pair<int, std::int64_t>(6, 419369)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test063) {
	constexpr auto state = chss::fen::Parse("6KQ/8/8/8/8/8/8/7k b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 2),
		std::pair<int, std::int64_t>(2, 36),
		std::pair<int, std::int64_t>(3, 143),
		std::pair<int, std::int64_t>(4, 3637),
		std::pair<int, std::int64_t>(5, 14893),
		std::pair<int, std::int64_t>(6, 391507)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test064) {
	constexpr auto state = chss::fen::Parse("K7/8/8/3Q4/4q3/8/8/7k b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 6),
		std::pair<int, std::int64_t>(2, 35),
		std::pair<int, std::int64_t>(3, 495),
		std::pair<int, std::int64_t>(4, 8349),
		std::pair<int, std::int64_t>(5, 166741),
		std::pair<int, std::int64_t>(6, 3370175)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test065) {
	constexpr auto state = chss::fen::Parse("8/8/8/8/8/K7/P7/k7 w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 3),
		std::pair<int, std::int64_t>(2, 7),
		std::pair<int, std::int64_t>(3, 43),
		std::pair<int, std::int64_t>(4, 199),
		std::pair<int, std::int64_t>(5, 1347),
		std::pair<int, std::int64_t>(6, 6249)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test066) {
	constexpr auto state = chss::fen::Parse("8/8/8/8/8/7K/7P/7k w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 3),
		std::pair<int, std::int64_t>(2, 7),
		std::pair<int, std::int64_t>(3, 43),
		std::pair<int, std::int64_t>(4, 199),
		std::pair<int, std::int64_t>(5, 1347),
		std::pair<int, std::int64_t>(6, 6249)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test067) {
	constexpr auto state = chss::fen::Parse("K7/p7/k7/8/8/8/8/8 w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 1),
		std::pair<int, std::int64_t>(2, 3),
		std::pair<int, std::int64_t>(3, 12),
		std::pair<int, std::int64_t>(4, 80),
		std::pair<int, std::int64_t>(5, 342),
		std::pair<int, std::int64_t>(6, 2343)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test068) {
	constexpr auto state = chss::fen::Parse("7K/7p/7k/8/8/8/8/8 w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 1),
		std::pair<int, std::int64_t>(2, 3),
		std::pair<int, std::int64_t>(3, 12),
		std::pair<int, std::int64_t>(4, 80),
		std::pair<int, std::int64_t>(5, 342),
		std::pair<int, std::int64_t>(6, 2343)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test069) {
	constexpr auto state = chss::fen::Parse("8/2k1p3/3pP3/3P2K1/8/8/8/8 w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 7),
		std::pair<int, std::int64_t>(2, 35),
		std::pair<int, std::int64_t>(3, 210),
		std::pair<int, std::int64_t>(4, 1091),
		std::pair<int, std::int64_t>(5, 7028),
		std::pair<int, std::int64_t>(6, 34834)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test070) {
	constexpr auto state = chss::fen::Parse("8/8/8/8/8/K7/P7/k7 b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 1),
		std::pair<int, std::int64_t>(2, 3),
		std::pair<int, std::int64_t>(3, 12),
		std::pair<int, std::int64_t>(4, 80),
		std::pair<int, std::int64_t>(5, 342),
		std::pair<int, std::int64_t>(6, 2343)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test071) {
	constexpr auto state = chss::fen::Parse("8/8/8/8/8/7K/7P/7k b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 1),
		std::pair<int, std::int64_t>(2, 3),
		std::pair<int, std::int64_t>(3, 12),
		std::pair<int, std::int64_t>(4, 80),
		std::pair<int, std::int64_t>(5, 342),
		std::pair<int, std::int64_t>(6, 2343)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test072) {
	constexpr auto state = chss::fen::Parse("K7/p7/k7/8/8/8/8/8 b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 3),
		std::pair<int, std::int64_t>(2, 7),
		std::pair<int, std::int64_t>(3, 43),
		std::pair<int, std::int64_t>(4, 199),
		std::pair<int, std::int64_t>(5, 1347),
		std::pair<int, std::int64_t>(6, 6249)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test073) {
	constexpr auto state = chss::fen::Parse("7K/7p/7k/8/8/8/8/8 b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 3),
		std::pair<int, std::int64_t>(2, 7),
		std::pair<int, std::int64_t>(3, 43),
		std::pair<int, std::int64_t>(4, 199),
		std::pair<int, std::int64_t>(5, 1347),
		std::pair<int, std::int64_t>(6, 6249)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test074) {
	constexpr auto state = chss::fen::Parse("8/2k1p3/3pP3/3P2K1/8/8/8/8 b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 5),
		std::pair<int, std::int64_t>(2, 35),
		std::pair<int, std::int64_t>(3, 182),
		std::pair<int, std::int64_t>(4, 1091),
		std::pair<int, std::int64_t>(5, 5408),
		std::pair<int, std::int64_t>(6, 34822)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test075) {
	constexpr auto state = chss::fen::Parse("8/8/8/8/8/4k3/4P3/4K3 w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 2),
		std::pair<int, std::int64_t>(2, 8),
		std::pair<int, std::int64_t>(3, 44),
		std::pair<int, std::int64_t>(4, 282),
		std::pair<int, std::int64_t>(5, 1814),
		std::pair<int, std::int64_t>(6, 11848)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test076) {
	constexpr auto state = chss::fen::Parse("4k3/4p3/4K3/8/8/8/8/8 b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 2),
		std::pair<int, std::int64_t>(2, 8),
		std::pair<int, std::int64_t>(3, 44),
		std::pair<int, std::int64_t>(4, 282),
		std::pair<int, std::int64_t>(5, 1814),
		std::pair<int, std::int64_t>(6, 11848)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test077) {
	constexpr auto state = chss::fen::Parse("8/8/7k/7p/7P/7K/8/8 w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 3),
		std::pair<int, std::int64_t>(2, 9),
		std::pair<int, std::int64_t>(3, 57),
		std::pair<int, std::int64_t>(4, 360),
		std::pair<int, std::int64_t>(5, 1969),
		std::pair<int, std::int64_t>(6, 10724)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test078) {
	constexpr auto state = chss::fen::Parse("8/8/k7/p7/P7/K7/8/8 w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 3),
		std::pair<int, std::int64_t>(2, 9),
		std::pair<int, std::int64_t>(3, 57),
		std::pair<int, std::int64_t>(4, 360),
		std::pair<int, std::int64_t>(5, 1969),
		std::pair<int, std::int64_t>(6, 10724)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test079) {
	constexpr auto state = chss::fen::Parse("8/8/3k4/3p4/3P4/3K4/8/8 w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 5),
		std::pair<int, std::int64_t>(2, 25),
		std::pair<int, std::int64_t>(3, 180),
		std::pair<int, std::int64_t>(4, 1294),
		std::pair<int, std::int64_t>(5, 8296),
		std::pair<int, std::int64_t>(6, 53138)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test080) {
	constexpr auto state = chss::fen::Parse("8/3k4/3p4/8/3P4/3K4/8/8 w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 8),
		std::pair<int, std::int64_t>(2, 61),
		std::pair<int, std::int64_t>(3, 483),
		std::pair<int, std::int64_t>(4, 3213),
		std::pair<int, std::int64_t>(5, 23599),
		std::pair<int, std::int64_t>(6, 157093)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test081) {
	constexpr auto state = chss::fen::Parse("8/8/3k4/3p4/8/3P4/3K4/8 w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 8),
		std::pair<int, std::int64_t>(2, 61),
		std::pair<int, std::int64_t>(3, 411),
		std::pair<int, std::int64_t>(4, 3213),
		std::pair<int, std::int64_t>(5, 21637),
		std::pair<int, std::int64_t>(6, 158065)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test082) {
	constexpr auto state = chss::fen::Parse("k7/8/3p4/8/3P4/8/8/7K w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 4),
		std::pair<int, std::int64_t>(2, 15),
		std::pair<int, std::int64_t>(3, 90),
		std::pair<int, std::int64_t>(4, 534),
		std::pair<int, std::int64_t>(5, 3450),
		std::pair<int, std::int64_t>(6, 20960)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test083) {
	constexpr auto state = chss::fen::Parse("8/8/7k/7p/7P/7K/8/8 b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 3),
		std::pair<int, std::int64_t>(2, 9),
		std::pair<int, std::int64_t>(3, 57),
		std::pair<int, std::int64_t>(4, 360),
		std::pair<int, std::int64_t>(5, 1969),
		std::pair<int, std::int64_t>(6, 10724)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test084) {
	constexpr auto state = chss::fen::Parse("8/8/k7/p7/P7/K7/8/8 b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 3),
		std::pair<int, std::int64_t>(2, 9),
		std::pair<int, std::int64_t>(3, 57),
		std::pair<int, std::int64_t>(4, 360),
		std::pair<int, std::int64_t>(5, 1969),
		std::pair<int, std::int64_t>(6, 10724)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test085) {
	constexpr auto state = chss::fen::Parse("8/8/3k4/3p4/3P4/3K4/8/8 b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 5),
		std::pair<int, std::int64_t>(2, 25),
		std::pair<int, std::int64_t>(3, 180),
		std::pair<int, std::int64_t>(4, 1294),
		std::pair<int, std::int64_t>(5, 8296),
		std::pair<int, std::int64_t>(6, 53138)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test086) {
	constexpr auto state = chss::fen::Parse("8/3k4/3p4/8/3P4/3K4/8/8 b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 8),
		std::pair<int, std::int64_t>(2, 61),
		std::pair<int, std::int64_t>(3, 411),
		std::pair<int, std::int64_t>(4, 3213),
		std::pair<int, std::int64_t>(5, 21637),
		std::pair<int, std::int64_t>(6, 158065)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test087) {
	constexpr auto state = chss::fen::Parse("8/8/3k4/3p4/8/3P4/3K4/8 b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 8),
		std::pair<int, std::int64_t>(2, 61),
		std::pair<int, std::int64_t>(3, 483),
		std::pair<int, std::int64_t>(4, 3213),
		std::pair<int, std::int64_t>(5, 23599),
		std::pair<int, std::int64_t>(6, 157093)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test088) {
	constexpr auto state = chss::fen::Parse("k7/8/3p4/8/3P4/8/8/7K b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 4),
		std::pair<int, std::int64_t>(2, 15),
		std::pair<int, std::int64_t>(3, 89),
		std::pair<int, std::int64_t>(4, 537),
		std::pair<int, std::int64_t>(5, 3309),
		std::pair<int, std::int64_t>(6, 21104)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test089) {
	constexpr auto state = chss::fen::Parse("7k/3p4/8/8/3P4/8/8/K7 w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 4),
		std::pair<int, std::int64_t>(2, 19),
		std::pair<int, std::int64_t>(3, 117),
		std::pair<int, std::int64_t>(4, 720),
		std::pair<int, std::int64_t>(5, 4661),
		std::pair<int, std::int64_t>(6, 32191)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test090) {
	constexpr auto state = chss::fen::Parse("7k/8/8/3p4/8/8/3P4/K7 w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 5),
		std::pair<int, std::int64_t>(2, 19),
		std::pair<int, std::int64_t>(3, 116),
		std::pair<int, std::int64_t>(4, 716),
		std::pair<int, std::int64_t>(5, 4786),
		std::pair<int, std::int64_t>(6, 30980)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test091) {
	constexpr auto state = chss::fen::Parse("k7/8/8/7p/6P1/8/8/K7 w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 5),
		std::pair<int, std::int64_t>(2, 22),
		std::pair<int, std::int64_t>(3, 139),
		std::pair<int, std::int64_t>(4, 877),
		std::pair<int, std::int64_t>(5, 6112),
		std::pair<int, std::int64_t>(6, 41874)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test092) {
	constexpr auto state = chss::fen::Parse("k7/8/7p/8/8/6P1/8/K7 w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 4),
		std::pair<int, std::int64_t>(2, 16),
		std::pair<int, std::int64_t>(3, 101),
		std::pair<int, std::int64_t>(4, 637),
		std::pair<int, std::int64_t>(5, 4354),
		std::pair<int, std::int64_t>(6, 29679)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test093) {
	constexpr auto state = chss::fen::Parse("k7/8/8/6p1/7P/8/8/K7 w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 5),
		std::pair<int, std::int64_t>(2, 22),
		std::pair<int, std::int64_t>(3, 139),
		std::pair<int, std::int64_t>(4, 877),
		std::pair<int, std::int64_t>(5, 6112),
		std::pair<int, std::int64_t>(6, 41874)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test094) {
	constexpr auto state = chss::fen::Parse("k7/8/6p1/8/8/7P/8/K7 w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 4),
		std::pair<int, std::int64_t>(2, 16),
		std::pair<int, std::int64_t>(3, 101),
		std::pair<int, std::int64_t>(4, 637),
		std::pair<int, std::int64_t>(5, 4354),
		std::pair<int, std::int64_t>(6, 29679)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test095) {
	constexpr auto state = chss::fen::Parse("k7/8/8/3p4/4p3/8/8/7K w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 3),
		std::pair<int, std::int64_t>(2, 15),
		std::pair<int, std::int64_t>(3, 84),
		std::pair<int, std::int64_t>(4, 573),
		std::pair<int, std::int64_t>(5, 3013),
		std::pair<int, std::int64_t>(6, 22886)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test096) {
	constexpr auto state = chss::fen::Parse("k7/8/3p4/8/8/4P3/8/7K w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 4),
		std::pair<int, std::int64_t>(2, 16),
		std::pair<int, std::int64_t>(3, 101),
		std::pair<int, std::int64_t>(4, 637),
		std::pair<int, std::int64_t>(5, 4271),
		std::pair<int, std::int64_t>(6, 28662)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test097) {
	constexpr auto state = chss::fen::Parse("7k/3p4/8/8/3P4/8/8/K7 b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 5),
		std::pair<int, std::int64_t>(2, 19),
		std::pair<int, std::int64_t>(3, 117),
		std::pair<int, std::int64_t>(4, 720),
		std::pair<int, std::int64_t>(5, 5014),
		std::pair<int, std::int64_t>(6, 32167)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test098) {
	constexpr auto state = chss::fen::Parse("7k/8/8/3p4/8/8/3P4/K7 b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 4),
		std::pair<int, std::int64_t>(2, 19),
		std::pair<int, std::int64_t>(3, 117),
		std::pair<int, std::int64_t>(4, 712),
		std::pair<int, std::int64_t>(5, 4658),
		std::pair<int, std::int64_t>(6, 30749)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test099) {
	constexpr auto state = chss::fen::Parse("k7/8/8/7p/6P1/8/8/K7 b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 5),
		std::pair<int, std::int64_t>(2, 22),
		std::pair<int, std::int64_t>(3, 139),
		std::pair<int, std::int64_t>(4, 877),
		std::pair<int, std::int64_t>(5, 6112),
		std::pair<int, std::int64_t>(6, 41874)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test100) {
	constexpr auto state = chss::fen::Parse("k7/8/7p/8/8/6P1/8/K7 b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 4),
		std::pair<int, std::int64_t>(2, 16),
		std::pair<int, std::int64_t>(3, 101),
		std::pair<int, std::int64_t>(4, 637),
		std::pair<int, std::int64_t>(5, 4354),
		std::pair<int, std::int64_t>(6, 29679)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test101) {
	constexpr auto state = chss::fen::Parse("k7/8/8/6p1/7P/8/8/K7 b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 5),
		std::pair<int, std::int64_t>(2, 22),
		std::pair<int, std::int64_t>(3, 139),
		std::pair<int, std::int64_t>(4, 877),
		std::pair<int, std::int64_t>(5, 6112),
		std::pair<int, std::int64_t>(6, 41874)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test102) {
	constexpr auto state = chss::fen::Parse("k7/8/6p1/8/8/7P/8/K7 b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 4),
		std::pair<int, std::int64_t>(2, 16),
		std::pair<int, std::int64_t>(3, 101),
		std::pair<int, std::int64_t>(4, 637),
		std::pair<int, std::int64_t>(5, 4354),
		std::pair<int, std::int64_t>(6, 29679)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test103) {
	constexpr auto state = chss::fen::Parse("k7/8/8/3p4/4p3/8/8/7K b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 5),
		std::pair<int, std::int64_t>(2, 15),
		std::pair<int, std::int64_t>(3, 102),
		std::pair<int, std::int64_t>(4, 569),
		std::pair<int, std::int64_t>(5, 4337),
		std::pair<int, std::int64_t>(6, 22579)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test104) {
	constexpr auto state = chss::fen::Parse("k7/8/3p4/8/8/4P3/8/7K b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 4),
		std::pair<int, std::int64_t>(2, 16),
		std::pair<int, std::int64_t>(3, 101),
		std::pair<int, std::int64_t>(4, 637),
		std::pair<int, std::int64_t>(5, 4271),
		std::pair<int, std::int64_t>(6, 28662)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test105) {
	constexpr auto state = chss::fen::Parse("7k/8/8/p7/1P6/8/8/7K w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 5),
		std::pair<int, std::int64_t>(2, 22),
		std::pair<int, std::int64_t>(3, 139),
		std::pair<int, std::int64_t>(4, 877),
		std::pair<int, std::int64_t>(5, 6112),
		std::pair<int, std::int64_t>(6, 41874)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test106) {
	constexpr auto state = chss::fen::Parse("7k/8/p7/8/8/1P6/8/7K w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 4),
		std::pair<int, std::int64_t>(2, 16),
		std::pair<int, std::int64_t>(3, 101),
		std::pair<int, std::int64_t>(4, 637),
		std::pair<int, std::int64_t>(5, 4354),
		std::pair<int, std::int64_t>(6, 29679)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test107) {
	constexpr auto state = chss::fen::Parse("7k/8/8/1p6/P7/8/8/7K w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 5),
		std::pair<int, std::int64_t>(2, 22),
		std::pair<int, std::int64_t>(3, 139),
		std::pair<int, std::int64_t>(4, 877),
		std::pair<int, std::int64_t>(5, 6112),
		std::pair<int, std::int64_t>(6, 41874)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test108) {
	constexpr auto state = chss::fen::Parse("7k/8/1p6/8/8/P7/8/7K w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 4),
		std::pair<int, std::int64_t>(2, 16),
		std::pair<int, std::int64_t>(3, 101),
		std::pair<int, std::int64_t>(4, 637),
		std::pair<int, std::int64_t>(5, 4354),
		std::pair<int, std::int64_t>(6, 29679)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test109) {
	constexpr auto state = chss::fen::Parse("k7/7p/8/8/8/8/6P1/K7 w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 5),
		std::pair<int, std::int64_t>(2, 25),
		std::pair<int, std::int64_t>(3, 161),
		std::pair<int, std::int64_t>(4, 1035),
		std::pair<int, std::int64_t>(5, 7574),
		std::pair<int, std::int64_t>(6, 55338)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test110) {
	constexpr auto state = chss::fen::Parse("k7/6p1/8/8/8/8/7P/K7 w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 5),
		std::pair<int, std::int64_t>(2, 25),
		std::pair<int, std::int64_t>(3, 161),
		std::pair<int, std::int64_t>(4, 1035),
		std::pair<int, std::int64_t>(5, 7574),
		std::pair<int, std::int64_t>(6, 55338)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test111) {
	constexpr auto state = chss::fen::Parse("3k4/3pp3/8/8/8/8/3PP3/3K4 w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 7),
		std::pair<int, std::int64_t>(2, 49),
		std::pair<int, std::int64_t>(3, 378),
		std::pair<int, std::int64_t>(4, 2902),
		std::pair<int, std::int64_t>(5, 24122),
		std::pair<int, std::int64_t>(6, 199002)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test112) {
	constexpr auto state = chss::fen::Parse("7k/8/8/p7/1P6/8/8/7K b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 5),
		std::pair<int, std::int64_t>(2, 22),
		std::pair<int, std::int64_t>(3, 139),
		std::pair<int, std::int64_t>(4, 877),
		std::pair<int, std::int64_t>(5, 6112),
		std::pair<int, std::int64_t>(6, 41874)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test113) {
	constexpr auto state = chss::fen::Parse("7k/8/p7/8/8/1P6/8/7K b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 4),
		std::pair<int, std::int64_t>(2, 16),
		std::pair<int, std::int64_t>(3, 101),
		std::pair<int, std::int64_t>(4, 637),
		std::pair<int, std::int64_t>(5, 4354),
		std::pair<int, std::int64_t>(6, 29679)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test114) {
	constexpr auto state = chss::fen::Parse("7k/8/8/1p6/P7/8/8/7K b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 5),
		std::pair<int, std::int64_t>(2, 22),
		std::pair<int, std::int64_t>(3, 139),
		std::pair<int, std::int64_t>(4, 877),
		std::pair<int, std::int64_t>(5, 6112),
		std::pair<int, std::int64_t>(6, 41874)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test115) {
	constexpr auto state = chss::fen::Parse("7k/8/1p6/8/8/P7/8/7K b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 4),
		std::pair<int, std::int64_t>(2, 16),
		std::pair<int, std::int64_t>(3, 101),
		std::pair<int, std::int64_t>(4, 637),
		std::pair<int, std::int64_t>(5, 4354),
		std::pair<int, std::int64_t>(6, 29679)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test116) {
	constexpr auto state = chss::fen::Parse("k7/7p/8/8/8/8/6P1/K7 b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 5),
		std::pair<int, std::int64_t>(2, 25),
		std::pair<int, std::int64_t>(3, 161),
		std::pair<int, std::int64_t>(4, 1035),
		std::pair<int, std::int64_t>(5, 7574),
		std::pair<int, std::int64_t>(6, 55338)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test117) {
	constexpr auto state = chss::fen::Parse("k7/6p1/8/8/8/8/7P/K7 b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 5),
		std::pair<int, std::int64_t>(2, 25),
		std::pair<int, std::int64_t>(3, 161),
		std::pair<int, std::int64_t>(4, 1035),
		std::pair<int, std::int64_t>(5, 7574),
		std::pair<int, std::int64_t>(6, 55338)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test118) {
	constexpr auto state = chss::fen::Parse("3k4/3pp3/8/8/8/8/3PP3/3K4 b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 7),
		std::pair<int, std::int64_t>(2, 49),
		std::pair<int, std::int64_t>(3, 378),
		std::pair<int, std::int64_t>(4, 2902),
		std::pair<int, std::int64_t>(5, 24122),
		std::pair<int, std::int64_t>(6, 199002)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test119) {
	constexpr auto state = chss::fen::Parse("8/Pk6/8/8/8/8/6Kp/8 w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 11),
		std::pair<int, std::int64_t>(2, 97),
		std::pair<int, std::int64_t>(3, 887),
		std::pair<int, std::int64_t>(4, 8048),
		std::pair<int, std::int64_t>(5, 90606),
		std::pair<int, std::int64_t>(6, 1030499)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test120) {
	constexpr auto state = chss::fen::Parse("n1n5/1Pk5/8/8/8/8/5Kp1/5N1N w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 24),
		std::pair<int, std::int64_t>(2, 421),
		std::pair<int, std::int64_t>(3, 7421),
		std::pair<int, std::int64_t>(4, 124608),
		std::pair<int, std::int64_t>(5, 2193768),
		std::pair<int, std::int64_t>(6, 37665329)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test121) {
	constexpr auto state = chss::fen::Parse("8/PPPk4/8/8/8/8/4Kppp/8 w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 18),
		std::pair<int, std::int64_t>(2, 270),
		std::pair<int, std::int64_t>(3, 4699),
		std::pair<int, std::int64_t>(4, 79355),
		std::pair<int, std::int64_t>(5, 1533145),
		std::pair<int, std::int64_t>(6, 28859283)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test122) {
	constexpr auto state = chss::fen::Parse("n1n5/PPPk4/8/8/8/8/4Kppp/5N1N w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 24),
		std::pair<int, std::int64_t>(2, 496),
		std::pair<int, std::int64_t>(3, 9483),
		std::pair<int, std::int64_t>(4, 182838),
		std::pair<int, std::int64_t>(5, 3605103),
		std::pair<int, std::int64_t>(6, 71179139)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test123) {
	constexpr auto state = chss::fen::Parse("8/Pk6/8/8/8/8/6Kp/8 b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 11),
		std::pair<int, std::int64_t>(2, 97),
		std::pair<int, std::int64_t>(3, 887),
		std::pair<int, std::int64_t>(4, 8048),
		std::pair<int, std::int64_t>(5, 90606),
		std::pair<int, std::int64_t>(6, 1030499)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test124) {
	constexpr auto state = chss::fen::Parse("n1n5/1Pk5/8/8/8/8/5Kp1/5N1N b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 24),
		std::pair<int, std::int64_t>(2, 421),
		std::pair<int, std::int64_t>(3, 7421),
		std::pair<int, std::int64_t>(4, 124608),
		std::pair<int, std::int64_t>(5, 2193768),
		std::pair<int, std::int64_t>(6, 37665329)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test125) {
	constexpr auto state = chss::fen::Parse("8/PPPk4/8/8/8/8/4Kppp/8 b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 18),
		std::pair<int, std::int64_t>(2, 270),
		std::pair<int, std::int64_t>(3, 4699),
		std::pair<int, std::int64_t>(4, 79355),
		std::pair<int, std::int64_t>(5, 1533145),
		std::pair<int, std::int64_t>(6, 28859283)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test126) {
	constexpr auto state = chss::fen::Parse("n1n5/PPPk4/8/8/8/8/4Kppp/5N1N b - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 24),
		std::pair<int, std::int64_t>(2, 496),
		std::pair<int, std::int64_t>(3, 9483),
		std::pair<int, std::int64_t>(4, 182838),
		std::pair<int, std::int64_t>(5, 3605103),
		std::pair<int, std::int64_t>(6, 71179139)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test127) {
	constexpr auto state = chss::fen::Parse("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");
	constexpr auto depthAndNodesVisited = std::array{
		std::pair<int, std::int64_t>(1, 14),
		std::pair<int, std::int64_t>(2, 191),
		std::pair<int, std::int64_t>(3, 2812),
		std::pair<int, std::int64_t>(4, 43238),
		std::pair<int, std::int64_t>(5, 674624),
		std::pair<int, std::int64_t>(6, 11030083)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}

TEST(Perft, Test128) {
	constexpr auto state = chss::fen::Parse("rnbqkb1r/ppppp1pp/7n/4Pp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3");
	constexpr auto depthAndNodesVisited = std::array{std::pair<int, std::int64_t>(5, 11139762)};
	for (const auto& [depth, nodesVisited] : depthAndNodesVisited) {
		if (depth > 4)
			continue;
		EXPECT_EQ(chss::MoveGeneration::Perft(state, depth), nodesVisited);
	}
}
